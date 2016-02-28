/*
 * r_bsp.c
 *
 * funções para desenhar arvores BSP
 *
 */

#if __DEBUG__
#include <stdio.h>
#endif

#include "common/vector.h"

#include "trace/trace.h"

#include "bsp/bsp.h"

#include "renderer.h"
#include "r_model.h"

void r_render_bsp_node(const bsp_node_t* node, const vec3_t eye)
{
	if(node == NULL)
		return;

	side_t side;
	side = tr_side_of_point(eye, node->normal, node->dist);

	unsigned long int i;
	switch(side)
	{
		case SAME:

			r_render_bsp_node(node->children[0], eye);

#if __DEBUG__
			for(i = 0; i < node->polygoncount; i++)
				r_render_polygon(&node->polygons[i]);
#endif

			r_render_bsp_node(node->children[1], eye);
			break;

		case FRONT:
			r_render_bsp_node(node->children[1], eye);

			for(i = 0; i < node->polygoncount; i++)
				r_render_polygon(&node->polygons[i]);

			r_render_bsp_node(node->children[0], eye);
			break;

		case BACK:	
			r_render_bsp_node(node->children[0], eye);

			for(i = 0; i < node->polygoncount; i++)
				r_render_polygon(&node->polygons[i]);

			r_render_bsp_node(node->children[1], eye);
			break;
	}
}

void r_render_bsp_tree(const bsp_tree_t* tree, const vec3_t eye)
{
	r_render_bsp_node(&tree->root, eye);
}

/* EOF */
