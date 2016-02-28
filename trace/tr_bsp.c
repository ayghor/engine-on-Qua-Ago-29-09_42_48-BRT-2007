/*
 * tr_bsp.c
 *
 * ray tracing para arvores BSP
 *
 */

#if __DEBUG__
#include <stdio.h>
#endif

#include <math.h>

#include "trace.h"
#include "tr_model.h"
#include "tr_bsp.h"

inline void tr_trace_vs_bsp_node(const vec3_t src, const vec3_t dir, const bsp_node_t* node, bool* collided, const bsp_node_t** rnode, vec3_t r, vec_t* t)
{
	vec3_t dest, r2;
	vec_t dist, destdist, t2;

	if(node == NULL)
		return;

	dist = vec3_dotproduct(src, node->normal);
	vec3_add(dest, src, dir);
	destdist = vec3_dotproduct(dest, node->normal);

	if(dist > node->dist + TR_EPSILON) /* origem está a frente */
	{
		if(destdist < dist) /* raio vai de frente pra trás */
		{
			tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);

			tr_trace_vs_plane(src, dir, node->normal, node->dist, r2, &t2);

			if(t2 < 0)
				puts("HOUSTON WE GOT A PROBLEM HERE");

			if(t2 <= *t) /* colisão ocorreu antes da anterior */
			{
				unsigned long int i;
				for(i = 0; i < node->polygoncount; i++)
				{
					if(tr_point_in_polygon(r2, &node->polygons[i]))
					{
						vec3_copy(r, r2);
						*t = t2;
						*collided = true;
						*rnode = node;

						tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);
						return;
					}
				}
			}


			tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);
			return;
		}

		if(destdist > dist) /* raio vai de trás pra frente */
		{
			tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);
			return;
		}

		/* raio segue paralelo ao plano */
		tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);
		return;
	}

	if(dist < node->dist - TR_EPSILON) /* origem está a trás */
	{
		if(destdist < dist) /* raio vai de frente pra trás */
		{
			tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);
			return;
		}

		if(destdist > dist) /* raio vai de trás pra frente */
		{
			tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);

			tr_trace_vs_plane(src, dir, node->normal, node->dist, r2, &t2);

			if(t2 < 0)
				puts("HOUSTON WE GOT A PROBLEM HERE");

			if(t2 <= *t) /* colisão ocorreu antes da anterior */
			{
				unsigned long int i;
				for(i = 0; i < node->polygoncount; i++)
				{
					if(tr_point_in_polygon(r2, &node->polygons[i]))
					{
						vec3_copy(r, r2);
						*t = t2;
						*collided = true;
						*rnode = node;

						tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);
						return;
					}
				}
			}
		
			tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);
			return;
		}

		/* raio segue paralelo ao plano */
		tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);
		return;
	}

	/* origem coincide com plano */
	if(destdist < dist) /* raio vai de frente pra trás */
	{
		tr_trace_vs_bsp_node(src, dir, node->children[1], collided, rnode, r, t);
		return;
	}

	if(destdist > dist) /* raio vai de trás pra frente */
	{
		tr_trace_vs_bsp_node(src, dir, node->children[0], collided, rnode, r, t);
		return;
	}

	/* raio segue paralelo ao plano */
	return;
}

/* EOF */
