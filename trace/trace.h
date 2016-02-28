/*
 * trace.h
 *
 * ray tracing
 *
 */

#ifndef __TRACE_H__
#define __TRACE_H__ 1

#include "common/boolean.h"
#include "common/vector.h"

#define TR_EPSILON 0.0000076

typedef enum side_e
{
	FRONT =	0,
	BACK =	1,
	SAME =	2
} side_t;

inline side_t tr_side_of_point(const vec3_t p, const vec3_t normal, vec_t dist);

inline void tr_trace_vs_plane(const vec3_t src, const vec3_t dir, const vec3_t normal, vec_t dist, vec3_t r, vec_t* t);

inline bool tr_point_in_area(const vec3_t p, const vec3_t* verts, unsigned int vertc, const vec3_t normal);

#endif /* __TRACE_H__ */

/* EOF */
