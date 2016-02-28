/*
 * renderer.h
 *
 * desenha entidades
 *
 */

#ifndef __RENDERER_H__
#define __RENDERER_H__ 1

/* FIXME não deveria haver entidades aqui */
#include "game/g_entity.h"

void r_init();
void r_fini();
void r_resizescene(unsigned int width, unsigned int height);
void r_renderer();
void r_render_map();
void r_render_entity(const g_entity_t* ent);

#endif /* __RENDERER_H__ */

/* EOF */
