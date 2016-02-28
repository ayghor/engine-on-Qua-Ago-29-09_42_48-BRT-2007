/*
 * g_entity.c
 *
 * funções para manipulação de entidades
 *
 */

#include <string.h>

#include "game/g_entity.h"

g_entity_t g_entities[G_ENTITIES_SIZE];
unsigned int g_entity_count = 0;

void g_entities_init()
{
	memset(g_entities, 0, G_ENTITIES_SIZE * sizeof(g_entity_t));
	g_entity_count = 0;
}

void g_entities_fini()
{
	return;
}

inline int g_entity_add(const g_entity_t* entity)
{
	unsigned int i;
	for(i = 0; i < G_ENTITIES_SIZE; i++)
	{
		if(!g_entities[i].active)
		{
			memcpy(&g_entities[i], entity, sizeof(g_entity_t));
			g_entities[i].active = true;
			g_entities[i].i = i;
			g_entity_count++;
			return 0;
		}
	}

	return -1;
}

inline int g_entity_del(unsigned int i)
{
	if(g_entities[i].active)
	{
		memset(&g_entities[i], 0, sizeof(g_entity_t));
		g_entity_count--;
		return 0;
	}

	return -1;
}

/* EOF */
