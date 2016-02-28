/*
 * r_bsp.h
 *
 * funções para desenhar arvores BSP
 *
 */

#ifndef __R_BSP_H__
#define __R_BSP_H__ 1 

#include "common/vector.h"
#include "bsp/bsp.h"

void r_render_bsp_node(const bsp_node_t* node, const vec3_t eye);
void r_render_bsp_tree(const bsp_tree_t* tree, const vec3_t eye);

#endif /* __R_BSP_H__ */

/* EOF */
