/*
 * model.c
 *
 * modelos 3d
 *
 */

#include <stdlib.h>
#include <string.h>

#include "common/vector.h"

#include "image.h"
#include "model.h"

void polygon_free(polygon_t* poly)
{
	free(poly->verts);
}

void polygon_copy(polygon_t* dest, const polygon_t* src)
{
	dest->verts = malloc(src->vertc * sizeof(vertex_t));
	memcpy(dest->verts, src->verts, src->vertc * sizeof(vertex_t));
	dest->vertc = src->vertc;

	vec3_copy(dest->normal, src->normal);
	dest->material = src->material;

	vec3_copy(dest->tex_shift, src->tex_shift);
	vec3_copy(dest->tex_rotation, src->tex_rotation);
	vec3_copy(dest->tex_scale, src->tex_scale);
}

void model_free(model_t* model)
{
	unsigned long int i;
	for(i = 0; i < model->polyc; i++)
		polygon_free(&model->polys[i]);

	free(model->materials);
	free(model->textures);
}


/* EOF */
