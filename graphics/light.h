/*
 * light.h
 *
 * luzes
 *
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__ 1

#include "common/vector.h"

/* luz */
typedef struct light_s
{
	vec4_t ambient_color;		/* luz de ambiente */
	vec4_t difuse_color;		/* luz difusa */
	vec4_t specular_color;		/* luz especular */

	vec3_t source;			/* origem */

	vec3_t spot_direction;		/* dire��o do foco */
	vec_t spot_exponent;		/* exponente de crescimento do foco */
	vec_t spot_cutoff;		/* algumacoisa */

	vec_t constant_attenuation;	/* atenua��o constante */
	vec_t linear_attenuation;	/* atenua��o linear */
	vec_t quadratic_attenuation;	/* atenua��o quadradica */
} light_t;

#endif /* __LIGHT_H__ */

/* EOF */
