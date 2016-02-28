/*
 * trace.c
 *
 * ray tracing
 *
 */

#include "trace.h"

inline side_t tr_side_of_point(const vec3_t p, const vec3_t normal, vec_t dist)
{
	vec_t pdist;
	pdist = vec3_dotproduct(p, normal);
	
	if(pdist > dist + TR_EPSILON)
		return FRONT;

	if(pdist < dist - TR_EPSILON)
		return BACK;

	return SAME;
}

inline void tr_trace_vs_plane(const vec3_t src, const vec3_t dir, const vec3_t normal, vec_t dist, vec3_t r, vec_t* t)
{
	*t = (dist - vec3_dotproduct(src, normal)) / vec3_dotproduct(dir, normal);

	vec3_scale(r, dir, *t);
	vec3_add(r, r, src);
}

inline bool tr_point_in_area(const vec3_t p, const vec3_t* verts, unsigned int vertc, const vec3_t normal)
{
	const vec3_t* last;
	vec3_t edge, cp;
	vec_t dist;

	last = &verts[vertc - 1];

	unsigned int i;
	for(i = 0; i < vertc; i++)
	{
		vec3_sub(edge, verts[i], *last);

		vec3_crossproduct(cp, edge, normal);
		dist = vec3_dotproduct(cp, verts[i]);
		if(vec3_dotproduct(cp, p) > dist + TR_EPSILON)
			return false;

		last = &verts[i];
	}

	return true;
}

/* EOF */
