/*
 * bsp_model.c
 *
 * funções para manipulação de modelos
 *
 */

#if __DEBUG__
#include <stdio.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "common/vector.h"
#include "trace/trace.h"

#include "graphics/model.h"

#include "bsp/bsp.h"
#include "bsp/bsp_model.h"

inline void bsp_split_polygon_edge_with_plane(const vertex_t* src, const vertex_t* dest, const vec3_t normal, vec_t dist, bool* split, vertex_t* r, vec_t* t)
{
	vec3_t edge, dir;
	vec_t len;

	vec3_sub(edge, dest->coords, src->coords);
	len = vec3_len(edge);

	vec3_scale(dir, edge, 1 / len);

	tr_trace_vs_plane(src->coords, dir, normal, dist, r->coords, t);

	if(fabs(*t) > len)
	{
		*split = false;
		return;
	}

	vec3_t sn, dn;

	vec3_scale(dn, dest->normal, (*t) / len);
	vec3_scale(sn, src->normal, (len - (*t)) / len);
	vec3_add(r->normal, sn, dn);
	vec3_normalize(r->normal, r->normal);
	*split = true;
}

#define addtofront(v)									\
{											\
	front->verts = realloc(front->verts, (front->vertc + 1) * sizeof(vertex_t));	\
	memcpy(&front->verts[front->vertc], (v), sizeof(vertex_t));			\
	front->vertc++;									\
}

#define addtoback(v)									\
{											\
	back->verts = realloc(back->verts, (back->vertc + 1) * sizeof(vertex_t));	\
	memcpy(&back->verts[back->vertc], (v), sizeof(vertex_t));			\
	back->vertc++;									\
}

void bsp_split_polygon_with_plane(const polygon_t* poly, const vec3_t normal, vec_t dist, bool* split, polygon_t* front, polygon_t* back)
{
	side_t side, lside, rside;
	vertex_t* last;
	vertex_t r;
	vec_t t;

	memset(front, 0, sizeof(polygon_t));
	memset(back, 0, sizeof(polygon_t));

	last = &poly->verts[poly->vertc - 1];
	lside = tr_side_of_point(last->coords, normal, dist);
	rside = lside;

	*split = false;

	if(poly->vertc < 3 && poly->vertc != 0)
	{
		fputs("HOUSTON HOUSTON WE GOT A PROBLEM!", stderr);
		fprintf(stderr, "SPLIT RECEIVED POLYGON WITH %d VERTICES!\n", poly->vertc);
		abort();
	}

	unsigned int i;
	for(i = 0; i < poly->vertc; i++)
	{
		side = tr_side_of_point(poly->verts[i].coords, normal, dist);

		switch(side)
		{
			case SAME:
				addtofront(&poly->verts[i]);
				addtoback(&poly->verts[i]);
				lside = SAME;
				break;

			case FRONT:
				if(rside == BACK)
					*split = true;

				switch(lside)
				{
					case FRONT:
					case SAME:
						break;

					case BACK:
						bsp_split_polygon_edge_with_plane(last, &poly->verts[i], normal, dist, split, &r, &t);

						addtofront(&r);
						addtoback(&r);
						break;	
				}

				addtofront(&poly->verts[i]);
				rside = FRONT;
				lside = FRONT;
				break;

			case BACK:
				if(rside == FRONT)
					*split = true;

				switch(lside)
				{
					case BACK:
					case SAME:
						break;

					case FRONT:
						bsp_split_polygon_edge_with_plane(last, &poly->verts[i], normal, dist, split, &r, &t);

						addtofront(&r);
						addtoback(&r);
						break;	
				}

				addtoback(&poly->verts[i]);
				rside = BACK;
				lside = BACK;
				break;
		}

		last = &poly->verts[i];
	}

	if(rside == FRONT || (*split))
	{
		vec3_copy(front->normal, poly->normal);
		front->material = poly->material;
		vec3_copy(front->tex_shift, poly->tex_shift);
		vec3_copy(front->tex_rotation, poly->tex_rotation);
		vec3_copy(front->tex_scale, poly->tex_scale);
	}

	else
	{
		front->vertc = 0;
		polygon_free(front);
	}

	if(rside == BACK || (*split))
	{
		vec3_copy(back->normal, poly->normal);
		back->material = poly->material;
		vec3_copy(back->tex_shift, poly->tex_shift);
		vec3_copy(back->tex_rotation, poly->tex_rotation);
		vec3_copy(back->tex_scale, poly->tex_scale);
	}

	else
	{
		back->vertc = 0;
		polygon_free(back);
	}

#if 0
	if(rside == SAME)
	{
		puts("rside is same!");
		front->vertc = 0;
		polygon_free(front);

		back->vertc = 0;
		polygon_free(back);
	}
#endif

	if(front->vertc < 3 && front->vertc != 0)
	{
		fputs("HOUSTON HOUSTON WE GOT A PROBLEM!", stderr);
		fprintf(stderr, "SPLIT MADE FRONT POLYGON WITH %d VERTICES!\n", front->vertc);
		abort();
	}

	if(back->vertc < 3 && back->vertc != 0)
	{
		fputs("HOUSTON HOUSTON WE GOT A PROBLEM!", stderr);
		fprintf(stderr, "SPLIT MADE BACK POLYGON WITH %d VERTICES!\n", back->vertc);
		abort();
	}


}

#undef addtofront
#undef addtoback

#define addtonode(p)										\
{												\
	node->polygons = realloc(node->polygons, (node->polygoncount + 1) * sizeof(polygon_t));	\
	polygon_copy(&node->polygons[node->polygoncount], (p));				\
	node->polygoncount++;									\
}

#define addtofront(p)										\
{												\
	front_list = realloc(front_list, (front_count + 1) * sizeof(polygon_t));		\
	polygon_copy(&front_list[front_count], (p));						\
	front_count++;										\
}

#define addtoback(p)										\
{												\
	back_list = realloc(back_list, (back_count + 1) * sizeof(polygon_t));			\
	polygon_copy(&back_list[back_count], (p));						\
	back_count++;										\
}

void bsp_make_node_from_polygons(bsp_node_t* node, bsp_node_t* parent, const side_t side_of_parent, const polygon_t* polys, unsigned long int polyc)
{
	polygon_t* front_list = NULL;
	polygon_t* back_list = NULL;

	unsigned long int front_count = 0;
	unsigned long int back_count = 0;

	polygon_t front, back;
	bool split;

	memset(node, 0, sizeof(bsp_node_t));

	vec3_copy(node->normal, polys[0].normal);
	node->dist = vec3_dotproduct(polys[0].verts[0].coords, node->normal);

	node->parent = parent;
	node->side_of_parent = side_of_parent;

	unsigned long int i;
	for(i = 0; i < polyc; i++)
	{
		bsp_split_polygon_with_plane(&polys[i], node->normal, node->dist, &split, &front, &back);

		if(front.vertc == 0 && back.vertc == 0)
		{
			addtonode(&polys[i]);
			continue;
		}

#if __DEBUG__
		if(i == 0)
		{
			puts("ERROR: first poligon not on node?!");
			abort();
		}
#endif

		if(front.vertc > 0)
		{
			addtofront(&front);
			polygon_free(&front);
		}

		if(back.vertc > 0)
		{
			addtoback(&back);
			polygon_free(&back);
		}
	}

#if __DEBUG__
	if(node->polygoncount == 0)
	{
		puts("ERROR: node without polygons?!");
		abort();
	}
#endif

	if(front_count > 0)
	{
		node->children[0] = malloc(sizeof(bsp_node_t));
		bsp_make_node_from_polygons(node->children[0], node, FRONT, front_list, front_count);
	}

	else
		node->children[0] = NULL;

	free(front_list);

	if(back_count > 0)
	{
		node->children[1] = malloc(sizeof(bsp_node_t));
		bsp_make_node_from_polygons(node->children[1], node, BACK, back_list, back_count);
	}

	else
		node->children[1] = NULL;

	free(back_list);
}

#undef addtonode
#undef addtofront
#undef addtoback

void bsp_make_tree_from_model(bsp_tree_t* tree, const model_t* model)
{
	polygon_t* polygons;

	polygons = malloc(sizeof(polygon_t) * model->polyc);
	memcpy(polygons, model->polys, sizeof(polygon_t) * model->polyc);

	tree->materials = malloc(sizeof(material_t) * model->materialc);
	memcpy(tree->materials, model->materials, sizeof(material_t) * model->materialc);
	tree->materialc = model->materialc;

	unsigned long int i;
	for(i = 0; i < model->polyc; i++)
	{
		polygons[i].material = polygons[i].material - model->materials + tree->materials;
	}

	bsp_make_node_from_polygons(&tree->root, NULL, SAME, polygons, model->polyc);

	free(polygons);
}

/* EOF */
