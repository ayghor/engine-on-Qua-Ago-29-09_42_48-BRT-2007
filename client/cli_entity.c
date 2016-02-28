/*
 * cli_entity.c
 *
 * funções para manipulação de entidades
 *
 */

#include <string.h>

#include "game/cli_entity.h"

g_entity_t cli_entities[G_ENTITIES_SIZE];
unsigned int cli_entity_count = 0;

void cli_entities_init()
{
	memset(cli_entities, 0, G_ENTITIES_SIZE * sizeof(g_entity_t));
	cli_entity_count = 0;
}

int cli_entity_add(const g_entity_t* entity)
{
	unsigned int i;
	for(i = 0; i < G_ENTITIES_SIZE; i++)
	{
		if(!cli_entities[i].active)
		{
			memcpy(&cli_entities[i], entity, sizeof(g_entity_t));
			cli_entities[i].active = true;
			cli_entities[i].i = i;
			cli_entity_count++;
			return 0;
		}
	}

	return -1;
}

int cli_entity_del(unsigned int i)
{
	if(cli_entities[i].active)
	{
		memset(&cli_entities[i], 0, sizeof(g_entity_t));
		cli_entity_count--;
		return 0;
	}

	return -1;
}


/* EOF */
