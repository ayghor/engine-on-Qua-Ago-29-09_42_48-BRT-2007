/*
 * tr_bsp.h
 *
 * ray tracing para arvore BSP
 *
 */

#ifndef __TR_BSP_H__
#define __TR_BSP_H__ 1

#include "common/vector.h"
#include "common/boolean.h"
#include "bsp/bsp.h"

inline void tr_trace_vs_bsp_node(const vec3_t src, const vec3_t dir, const bsp_node_t* node, bool* collided, const bsp_node_t** rnode, vec3_t r, vec_t* t);

#endif /* __TR_BSP_H__ */

/* EOF */
