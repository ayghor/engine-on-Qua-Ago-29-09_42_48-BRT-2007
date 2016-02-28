/*
 * g_entity.h
 *
 * funções para manipulação de entidades
 *
 */

#ifndef __G_ENTITY_H__
#define __G_ENTITY_H__ 1

#include "common/boolean.h"
#include "common/vector.h"

#include "graphics/model.h"
#include "graphics/light.h"

#define G_ENTITIES_SIZE 16

typedef struct g_entity_s
{
	bool active;
	unsigned int i;

	vec3_t src;
	vec3_t scale;
	vec3_t rot;

	vec3_t dir;
	vec_t speed;

	vec3_t bbsrc;
	vec3_t bbsize;

	model_t* model;
} g_entity_t;

extern g_entity_t g_entities[G_ENTITIES_SIZE];
extern unsigned int g_entity_count;

void g_entities_init();
void g_entities_fini();
inline int g_entity_add(const g_entity_t* entity);
inline int g_entity_del(unsigned int i);

#endif /* __G_ENTITY_H__ */

/* EOF */
