/*
 * image.h
 *
 * Funções para manipulação de imagens
 *
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__ 1

#include <GL/gl.h>

/* imagem */
typedef struct image_s
{
	GLubyte gl_texnum;		/* número da textura */

	unsigned long int width;	/* largura */
	unsigned long int height;	/* altura */
	unsigned long int depth;	/* profundidade (cor) */

	unsigned short int components;	/* número dos componentes de cor */

	char* data;			/* imagem */
} image_t;

void image_load_texture(image_t* image);
void image_unload_texture(image_t* image);
void image_free(image_t* image);

#endif /* __IMAGE_H__ */

/* EOF */
