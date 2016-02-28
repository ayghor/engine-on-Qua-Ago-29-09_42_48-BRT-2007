/*
 * vector.h
 *
 * Funções para manipulação de vetores
 *
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__ 1

#include <math.h>

typedef double	vec_t;		/* escalar */
typedef vec_t	vec2_t[2];	/* vetor bidimensional */
typedef vec_t	vec3_t[3];	/* vetor tridimensional */
typedef vec_t	vec4_t[4];	/* vetor quadridimensional */

typedef float	fvec_t;		/* escalar */
typedef fvec_t	fvec2_t[2];	/* vetor bidimensional */
typedef fvec_t	fvec3_t[3];	/* vetor tridimensional */
typedef fvec_t	fvec4_t[4];	/* vetor quadridimensional */

inline void vec2_init(vec2_t vec, vec_t x, vec_t y);
inline void vec3_init(vec3_t vec, vec_t x, vec_t y, vec_t z);
inline void vec4_init(vec4_t vec, vec_t x, vec_t y, vec_t z, vec_t w);

inline void vec3_reflect(vec3_t vec, const vec3_t a, const vec3_t normal);

#define vec2_copy(v, a) vec2_init((v), (a)[0], (a)[1])
#define vec3_copy(v, a) vec3_init((v), (a)[0], (a)[1], (a)[2])
#define vec4_copy(v, a) vec4_init((v), (a)[0], (a)[1], (a)[2], (a)[3])

#define vec2_len(v) (sqrt(fabs((v)[0] * (v)[0] + (v)[1] * (v)[1])))
#define vec3_len(v) (sqrt(fabs((v)[0] * (v)[0] + (v)[1] * (v)[1] + (v)[2] * (v)[2])))
#define vec4_len(v) (sqrt(fabs((v)[0] * (v)[0] + (v)[1] * (v)[1] + (v)[2] * (v)[2] + (v)[3] * (v)[3])))

#define vec2_scale(v, a, s) vec2_init((v), (a)[0] * (s), (a)[1] * (s))
#define vec3_scale(v, a, s) vec3_init((v), (a)[0] * (s), (a)[1] * (s), (a)[2] * (s))
#define vec4_scale(v, a, s) vec4_init((v), (a)[0] * (s), (a)[1] * (s), (a)[2] * (s), (a)[3] * (s))

#define vec2_normalize(v, a) vec2_scale((v), (a), 1 / vec2_len((a)))
#define vec3_normalize(v, a) vec3_scale((v), (a), 1 / vec3_len((a)))
#define vec4_normalize(v, a) vec4_scale((v), (a), 1 / vec4_len((a)))

#define vec2_add(v, a, b) vec2_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1])
#define vec3_add(v, a, b) vec3_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1], (a)[2] + (b)[2])
#define vec4_add(v, a, b) vec4_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1], (a)[2] + (b)[2], (a)[3] + (b)[3])

#define vec2_sub(v, a, b) vec2_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1])
#define vec3_sub(v, a, b) vec3_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1], (a)[2] - (b)[2])
#define vec4_sub(v, a, b) vec4_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1], (a)[2] - (b)[2], (a)[3] - (b)[3])

#define vec2_mul(v, a, b) vec2_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1])
#define vec3_mul(v, a, b) vec3_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1], (a)[2] * (b)[2])
#define vec4_mul(v, a, b) vec4_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1], (a)[2] * (b)[2], (a)[3] * (b)[3])

#define vec2_div(v, a, b) vec2_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1])
#define vec3_div(v, a, b) vec3_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1], (a)[2] / (b)[2])
#define vec4_div(v, a, b) vec4_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1], (a)[2] / (b)[2], (a)[3] / (b)[3])

#define vec2_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1])
#define vec3_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2])
#define vec4_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2] && (a)[3] == (b)[3])

#define vec3_crossproduct(v, a, b) vec3_init((v), (a)[1] * (b)[2] - (a)[2] * (b)[1], (a)[2] * (b)[0] - (a)[0] * (b)[2], (a)[0] * (b)[1] - (a)[1] * (b)[0])

#define vec2_dotproduct(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1])
#define vec3_dotproduct(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])

inline void fvec2_init(fvec2_t fvec, fvec_t x, fvec_t y);
inline void fvec3_init(fvec3_t fvec, fvec_t x, fvec_t y, fvec_t z);
inline void fvec4_init(fvec4_t fvec, fvec_t x, fvec_t y, fvec_t z, fvec_t w);

inline void fvec3_reflect(fvec3_t fvec, const fvec3_t a, const fvec3_t normal);

#define fvec2_copy(v, a) fvec2_init((v), (a)[0], (a)[1])
#define fvec3_copy(v, a) fvec3_init((v), (a)[0], (a)[1], (a)[2])
#define fvec4_copy(v, a) fvec4_init((v), (a)[0], (a)[1], (a)[2], (a)[3])

#define fvec2_len(v) (sqrtf(fabsf((v)[0] * (v)[0] + (v)[1] * (v)[1])))
#define fvec3_len(v) (sqrtf(fabsf((v)[0] * (v)[0] + (v)[1] * (v)[1] + (v)[2] * (v)[2])))
#define fvec4_len(v) (sqrtf(fabsf((v)[0] * (v)[0] + (v)[1] * (v)[1] + (v)[2] * (v)[2] + (v)[3] * (v)[3])))

#define fvec2_scale(v, a, s) fvec2_init((v), (a)[0] * (s), (a)[1] * (s))
#define fvec3_scale(v, a, s) fvec3_init((v), (a)[0] * (s), (a)[1] * (s), (a)[2] * (s))
#define fvec4_scale(v, a, s) fvec4_init((v), (a)[0] * (s), (a)[1] * (s), (a)[2] * (s), (a)[3] * (s))

#define fvec2_normalize(v, a) fvec2_scale((v), (a), 1 / fvec2_len((a)))
#define fvec3_normalize(v, a) fvec3_scale((v), (a), 1 / fvec3_len((a)))
#define fvec4_normalize(v, a) fvec4_scale((v), (a), 1 / fvec4_len((a)))

#define fvec2_add(v, a, b) fvec2_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1])
#define fvec3_add(v, a, b) fvec3_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1], (a)[2] + (b)[2])
#define fvec4_add(v, a, b) fvec4_init((v), (a)[0] + (b)[0], (a)[1] + (b)[1], (a)[2] + (b)[2], (a)[3] + (b)[3])

#define fvec2_sub(v, a, b) fvec2_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1])
#define fvec3_sub(v, a, b) fvec3_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1], (a)[2] - (b)[2])
#define fvec4_sub(v, a, b) fvec4_init((v), (a)[0] - (b)[0], (a)[1] - (b)[1], (a)[2] - (b)[2], (a)[3] - (b)[3])

#define fvec2_mul(v, a, b) fvec2_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1])
#define fvec3_mul(v, a, b) fvec3_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1], (a)[2] * (b)[2])
#define fvec4_mul(v, a, b) fvec4_init((v), (a)[0] * (b)[0], (a)[1] * (b)[1], (a)[2] * (b)[2], (a)[3] * (b)[3])

#define fvec2_div(v, a, b) fvec2_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1])
#define fvec3_div(v, a, b) fvec3_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1], (a)[2] / (b)[2])
#define fvec4_div(v, a, b) fvec4_init((v), (a)[0] / (b)[0], (a)[1] / (b)[1], (a)[2] / (b)[2], (a)[3] / (b)[3])

#define fvec2_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1])
#define fvec3_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2])
#define fvec4_isequal(a, b) ((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2] && (a)[3] == (b)[3])

#define fvec3_crossproduct(v, a, b) fvec3_init((v), (a)[1] * (b)[2] - (a)[2] * (b)[1], (a)[2] * (b)[0] - (a)[0] * (b)[2], (a)[0] * (b)[1] - (a)[1] * (b)[0])

#define fvec2_dotproduct(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1])
#define fvec3_dotproduct(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])

#endif /* __VECTOR_H__ */

/* EOF */
