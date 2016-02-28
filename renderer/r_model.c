/*
 * r_model.c
 *
 * Funções para desenho de modelos 3d
 *
 */

#include <GL/gl.h>

#include "common/vector.h"

#include "graphics/model.h"
#include "graphics/image.h"

#include "renderer.h"
#include "r_model.h"

static material_t* lmaterial = NULL;

inline void r_loadtexture(image_t* texture)
{
/*	if(texture->gl_texnum != 0)
		return;

	glGenTextures(1, &texture->gl_texnum);
	glBindTexture(GL_TEXTURE_2D, texture->gl_texnum);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

	glTexImage2D(GL_TEXTURE_2D, level, 4, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);*/
}

inline void r_render_vertex(const vertex_t* vert)
{
	glNormal3dv(vert->normal);
	glVertex3dv(vert->coords);
}

inline void r_render_point(const vertex_t* vert)
{
	glBegin(GL_POINTS);
	r_render_vertex(vert);
	glEnd();
}

inline void r_render_line(const vertex_t* verta, const vertex_t* vertb)
{
	glBegin(GL_LINES);
	r_render_vertex(verta);
	r_render_vertex(vertb);
	glEnd();	
}

inline void r_render_polygon(const polygon_t* poly)
{
	if(lmaterial != poly->material)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, poly->material->ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, poly->material->diffuse_color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, poly->material->specular_color);
		glMaterialf(GL_FRONT, GL_SHININESS, poly->material->shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, poly->material->emission_color);
		lmaterial = poly->material;
	}

	/*glBindTexture(GL_TEXTURE_2D, poly->texture->texnum);*/

	glBegin(GL_POLYGON);

	unsigned int i;
	for(i = 0; i < poly->vertc; i++)
	{
		/*glTexCoord2dv()*/
		r_render_vertex(&poly->verts[i]);
	}
	glEnd();
}

inline void r_render_model(const model_t* model)
{
	unsigned long int i;
	for(i = 0; i < model->polyc; i++)
		r_render_polygon(&model->polys[i]);
}

/* EOF */
