/*
 * model.h
 *
 * modelos 3d
 *
 */

#ifndef __MODEL_H__
#define __MODEL_H__ 1

#include "common/vector.h"

#include "graphics/image.h"

/* vertice */
typedef struct vertex_s
{
	vec3_t coords;			/* coordenadas */
	vec3_t normal;			/* vetor normal */
} vertex_t;

/* material */
typedef struct material_s
{
	fvec4_t ambient_color;		/* reflexão de luz ambiental */
	fvec4_t diffuse_color;		/* reflexão de luz difusa */
	fvec4_t specular_color;		/* reflexão de luz especular */
	fvec_t shininess;		/* exponente de reflexão especular */
	fvec4_t emission_color;		/* luz emitida */
} material_t;

/* poligono */
typedef struct polygon_s
{
	vertex_t* verts;
	unsigned int vertc;

	vec3_t normal;

	material_t* material;

	vec3_t tex_shift;
	vec3_t tex_rotation;
	vec3_t tex_scale;
} polygon_t;

/* modelo */
typedef struct model_s
{
	polygon_t* polys;		/* poligonos */
	unsigned long int polyc;	/* número de poligonos */

	material_t* materials;		/* materiais */
	unsigned int materialc;		/* número de materiais */

	image_t* textures;		/* texturas */
	unsigned int texturec;		/* número de texturas */

} model_t;

void polygon_copy(polygon_t* dest, const polygon_t* src);
void polygon_free(polygon_t* poly);
void model_free(model_t* model);

#endif /* __MODEL_H__ */

/* EOF */
