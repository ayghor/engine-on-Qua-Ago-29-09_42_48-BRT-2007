/*
 * bsp.c
 *
 * Binary Space Partitioning
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/vector.h"
#include "common/rwmacros.h"

#include "bsp/bsp.h"

void bsp_node_write(const bsp_tree_t* tree, bsp_node_t* node, FILE* fp)
{
	if(node == NULL)
	{
		unsigned long int long_zero = 0;
		write_long(fp, &long_zero);
		return;
	}

	write_long(fp, &node->polygoncount);

	unsigned long int i;
	for(i = 0; i < node->polygoncount; i++)
	{
		write_long(fp, &node->polygons[i].vertc);

		unsigned int j;
		for(j = 0; j < node->polygons[i].vertc; j++)
		{
			write_vec3(fp, node->polygons[i].verts[j].coords);
			write_vec3(fp, node->polygons[i].verts[j].normal);
		}

		write_vec3(fp, node->polygons[i].normal);

		unsigned long int index;
		//index = (node->polygons[i].material - tree->materials) / sizeof(material_t);
		index = (node->polygons[i].material - tree->materials) / sizeof(material_t);

		write_long(fp, &index);

//		write_long(fp, &index);
//		node->polygons[i].texture = &tree->textures[index];
		
		write_vec2(fp, node->polygons[i].tex_shift);
		write_vec2(fp, node->polygons[i].tex_rotation);
		write_vec2(fp, node->polygons[i].tex_scale);	
	}

	write_vec(fp, &node->dist);
	write_vec3(fp, node->normal);

	/*node->parent = parent;*/
	write_int(fp, &node->side_of_parent);

	bsp_node_write(tree, node->children[0], fp);
	bsp_node_write(tree, node->children[1], fp);
}

int bsp_tree_write(bsp_tree_t* tree, const char* filename)
{
	FILE* fp;
	fp = fopen(filename, "wb");

	if(fp == NULL)
		return -1;

	write_long(fp, &tree->materialc);

	unsigned long int i;
	for(i = 0; i < tree->materialc; i++)
	{
		write_fvec4(fp, tree->materials[i].ambient_color);
		write_fvec4(fp, tree->materials[i].diffuse_color);
		write_fvec4(fp, tree->materials[i].specular_color);
		write_fvec(fp, &tree->materials[i].shininess);
		write_fvec4(fp, tree->materials[i].emission_color);
	}

	bsp_node_write(tree, &tree->root, fp);
	return 0;
}

void bsp_node_read(const bsp_tree_t* tree, bsp_node_t* node, bsp_node_t* parent, FILE* fp)
{
	read_long(fp, &node->polygoncount);
	if(node->polygoncount == 0)
		return;

	node->polygons = malloc(node->polygoncount * sizeof(polygon_t));

	unsigned long int i;
	for(i = 0; i < node->polygoncount; i++)
	{
		read_long(fp, &node->polygons[i].vertc);
		node->polygons[i].verts = malloc(node->polygons[i].vertc * sizeof(vertex_t));

		unsigned int j;
		for(j = 0; j < node->polygons[i].vertc; j++)
		{
			read_vec3(fp, node->polygons[i].verts[j].coords);
			read_vec3(fp, node->polygons[i].verts[j].normal);
		}

		read_vec3(fp, node->polygons[i].normal);

		unsigned long int index;
		read_long(fp, &index);
		node->polygons[i].material = &tree->materials[index];

//		read_long(fp, &index);
//		node->polygons[i].texture = &tree->textures[index];
		
		read_vec2(fp, node->polygons[i].tex_shift);
		read_vec2(fp, node->polygons[i].tex_rotation);
		read_vec2(fp, node->polygons[i].tex_scale);
	}

	read_vec(fp, &node->dist);
	read_vec3(fp, node->normal);

	node->parent = parent;
	read_int(fp, &node->side_of_parent);

	node->children[0] = malloc(sizeof(bsp_node_t));
	bsp_node_read(tree, node->children[0], node, fp);
	if(node->children[0]->polygoncount == 0)
	{
		free(node->children[0]);
		node->children[0] = NULL;
	}

	node->children[1] = malloc(sizeof(bsp_node_t));
	bsp_node_read(tree, node->children[1], node, fp);
	if(node->children[1]->polygoncount == 0)
	{
		free(node->children[1]);
		node->children[1] = NULL;
	}
}

int bsp_tree_read(bsp_tree_t* tree, const char* filename)
{
	FILE* fp;
	fp = fopen(filename, "rb");

	if(fp == NULL)
		return -1;

	read_long(fp, &tree->materialc);
	tree->materials = malloc(tree->materialc * sizeof(material_t));

	unsigned long int i;
	for(i = 0; i < tree->materialc; i++)
	{
		read_fvec4(fp, tree->materials[i].ambient_color);
		read_fvec4(fp, tree->materials[i].diffuse_color);
		read_fvec4(fp, tree->materials[i].specular_color);
		read_fvec(fp, &tree->materials[i].shininess);
		read_fvec4(fp, tree->materials[i].emission_color);
	}

	bsp_node_read(tree, &tree->root, NULL, fp);
	return 0;
}

void bsp_node_free(bsp_node_t* node)
{
	unsigned long int i;
	for(i = 0; i < node->polygoncount; i++)
		polygon_free(&node->polygons[i]);

	free(node->polygons);

	bsp_node_free(node->children[0]);
	free(node->children[0]);

	bsp_node_free(node->children[1]);
	free(node->children[1]);
}

void bsp_tree_free(bsp_tree_t* tree)
{
	free(tree->materials);
	bsp_node_free(&tree->root);
}

inline void bsp_split_edge_with_plane(const vec3_t src, const vec3_t dest, const vec3_t normal, vec_t dist, bool* split, vec3_t r, vec_t* t)
{
	vec3_t edge, dir;

	vec3_sub(edge, dest, src);
	vec3_normalize(dir, edge);

	tr_trace_vs_plane(src, dir, normal, dist, r, t);

	if(fabs(*t) > vec3_len(dir))
	{
		*split = false;
		return;
	}

	*split = true;
}

/* EOF */
