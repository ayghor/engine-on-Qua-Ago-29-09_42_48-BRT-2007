/*
 * bsp_model.h
 *
 * Binary Space Partitioning
 *
 * estruturas de dados de uma bsp tree
 *
 */

#ifndef __BSP_MODEL_H__
#define __BSP_MODEL_H__ 1

#include "graphics/model.h"

#include "bsp.h"

inline void bsp_split_polygon_edge_with_plane(const vertex_t* src, const vertex_t* dest, const vec3_t normal, vec_t dist, bool* split, vertex_t* r, vec_t* t);

void bsp_split_polygon_with_plane(const polygon_t* poly, const vec3_t normal, vec_t dist, bool* split, polygon_t* front, polygon_t* back);

void bsp_make_tree_from_model(bsp_tree_t* tree, const model_t* model);

#endif /* __BSP_MODEL_H__ */

/* EOF */
