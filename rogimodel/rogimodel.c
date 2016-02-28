/*
 * rogimodel.c
 *
 * Funções para manipulação de modelos rogi
 *
 */

/* C/C99 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graphics/model.h"
#include "rogimodel/rogimodel.h"

#include "common/rwmacros.h"

int rogimodel_read(model_t* model, const char* filename)
{
	FILE* fp;
	fp = fopen(filename, "rb");

	if(fp == NULL)
		return -1;

	memset(model, 0, sizeof(model_t));

	read_int(fp, &model->materialc);
	model->materials = calloc(model->materialc, sizeof(material_t));
	//printf("model has %ld materials.\n", model->materialc);

	unsigned long int i;
	for(i = 0; i < model->materialc; i++)
	{
		read_fvec4(fp, model->materials[i].ambient_color);
		read_fvec4(fp, model->materials[i].diffuse_color);
		read_fvec4(fp, model->materials[i].specular_color);
		read_fvec(fp, &model->materials[i].shininess);
		read_fvec4(fp, model->materials[i].emission_color);
	}

	read_long(fp, &model->polyc);
	model->polys = calloc(model->polyc, sizeof(polygon_t));
	//printf("model has %ld polygons.\n", model->polyc);

	for(i = 0; i < model->polyc; i++)
	{
		read_int(fp, &model->polys[i].vertc);
		model->polys[i].verts = calloc(model->polys[i].vertc, sizeof(vertex_t));

		unsigned int j;
		for(j = 0; j < model->polys[i].vertc; j++)
		{
			read_vec3(fp, model->polys[i].verts[j].coords);
			read_vec3(fp, model->polys[i].verts[j].normal);
		}

		read_vec3(fp, model->polys[i].normal);

		read_int(fp, &j);
		model->polys[i].material = &model->materials[j];
		
		read_vec2(fp, model->polys[i].tex_shift);
		read_vec2(fp, model->polys[i].tex_rotation);
		read_vec2(fp, model->polys[i].tex_scale);
	}

	fclose(fp);
	return 0;
}

/* EOF */
