/*
 * vector.c
 *
 * Funções para manipulação de vetores
 *
 */

#include "common/vector.h"

inline void vec2_init(vec2_t vec, vec_t x, vec_t y)
{
	vec[0] = x;
	vec[1] = y;
}

inline void vec3_init(vec3_t vec, vec_t x, vec_t y, vec_t z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

inline void vec4_init(vec4_t vec, vec_t x, vec_t y, vec_t z, vec_t w)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
}

inline void vec3_reflect(vec3_t vec, const vec3_t a, const vec3_t normal)
{
	vec3_t res;

	vec3_scale(res, normal, 2 * -vec3_dotproduct(a, normal));
	vec3_add(res, a, res);
	vec3_copy(vec, res);
}

inline void fvec2_init(fvec2_t fvec, fvec_t x, fvec_t y)
{
	fvec[0] = x;
	fvec[1] = y;
}

inline void fvec3_init(fvec3_t fvec, fvec_t x, fvec_t y, fvec_t z)
{
	fvec[0] = x;
	fvec[1] = y;
	fvec[2] = z;
}

inline void fvec4_init(fvec4_t fvec, fvec_t x, fvec_t y, fvec_t z, fvec_t w)
{
	fvec[0] = x;
	fvec[1] = y;
	fvec[2] = z;
	fvec[3] = w;
}

inline void fvec3_reflect(fvec3_t fvec, const fvec3_t a, const fvec3_t normal)
{
	fvec3_t res;

	fvec3_scale(res, normal, 2 * -fvec3_dotproduct(a, normal));
	fvec3_add(res, a, res);
	fvec3_copy(fvec, res);
}


/* EOF */
