/*
 * image.c
 *
 * Funções para manipulação de imagens
 *
 */

#include <stdlib.h>

#include "image.h"

void image_load_texture(image_t* image)
{
	return;
}

void image_unload_texture(image_t* image)
{
	return;
}

void image_free(image_t* image)
{
	free(image->data);
}

/* EOF */
