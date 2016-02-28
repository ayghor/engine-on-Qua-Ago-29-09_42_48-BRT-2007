/*
 * r_g_entity.c
 *
 * funções para desenhar entidades
 *
 */

#include "game/g_entity.h"

#include "r_model.h"
#include "r_g_entity.h"

void r_render_g_entity(const g_entity_t* ent)
{
	glPushMatrix();

	glTranslated(ent->src[0], ent->src[1], ent->src[2]);
	glScaled(ent->scale[0], ent->scale[1], ent->scale[2]);
	glRotated(ent->rot[0], 1, 0, 0);
	glRotated(ent->rot[1], 0, 1, 0);
	glRotated(ent->rot[2], 0, 0, 1);

	r_render_model(ent->model);

	glPopMatrix();
}

/* EOF */
