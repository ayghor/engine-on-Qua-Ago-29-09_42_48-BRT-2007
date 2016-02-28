/*
 * bsp.h
 *
 * Binary Space Partitioning
 *
 * estruturas de dados de uma bsp tree
 *
 */

#ifndef __BSP_H__
#define __BSP_H__ 1

#include "graphics/model.h"
#include "trace/trace.h"

typedef struct bsp_node_s
{
	vec_t dist;
	vec3_t normal;

	polygon_t* polygons;
	unsigned long int polygoncount;

	struct bsp_node_s* parent;
	side_t side_of_parent;

	struct bsp_node_s* children[2];
} bsp_node_t;

typedef struct bsp_tree_s
{
	bsp_node_t root;

	material_t* materials;
	unsigned long int materialc;
} bsp_tree_t;

inline void bsp_split_edge_with_plane(const vec3_t src, const vec3_t dest, const vec3_t normal, vec_t dist, bool* split, vec3_t r, vec_t* t);

int bsp_tree_write(bsp_tree_t* tree, const char* filename);
int bsp_tree_read(bsp_tree_t* tree, const char* filename);

void bsp_tree_free(bsp_tree_t* tree);

#endif /* __BSP_H__ */

/* EOF */
