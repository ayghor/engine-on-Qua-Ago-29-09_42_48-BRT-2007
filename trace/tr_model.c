/*
 * tr_model.c
 *
 * ray tracing para modelos 3d
 *
 */

#if __DEBUG__
#include <stdio.h>
#endif

#include "common/boolean.h"
#include "graphics/model.h"

#include "trace.h"
#include "tr_model.h"

#if 0
inline bool tr_point_in_polygon(const vec3_t p, const polygon_t* poly)
{
	vec3_t* last;
	last = &poly->verts[poly->vertc - 1].coords;

	unsigned int i;
	for(i = 0; i < poly->vertc; i++)
	{
		vec3_t edge, res, cp;

		vec3_sub(edge, poly->verts[i].coords, *last);
		vec3_sub(res, p, *last);
		vec3_crossproduct(cp, edge, res);

		printf("uireh %d from %d = %lf. epsilon = %lf\n", i, poly->vertc, vec3_dotproduct(cp, poly->normal), TR_EPSILON);

		if(vec3_dotproduct(cp, poly->normal) < TR_EPSILON)
			return false;

		last = &poly->verts[i].coords;
	}

	return true;
}
#endif

inline bool tr_point_in_polygon(const vec3_t p, const polygon_t* poly)
{
	vec3_t *last, edge, cp;
	vec_t dist;

	last = &poly->verts[poly->vertc - 1].coords;

	unsigned int i;
	for(i = 0; i < poly->vertc; i++)
	{
		vec3_sub(edge, poly->verts[i].coords, *last);

		vec3_crossproduct(cp, edge, poly->normal);
		dist = vec3_dotproduct(cp, poly->verts[i].coords);
		if(vec3_dotproduct(cp, p) > dist + TR_EPSILON)
			return false;

		last = &poly->verts[i].coords;
	}

	return true;
}


/* EOF */
