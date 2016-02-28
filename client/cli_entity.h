/*
 * cli_entity.h
 *
 * funções para manipulação de entidades
 *
 */

#ifndef __CLI_ENTITY_H__
#define __CLI_ENTITY_H__ 1

#include "common/boolean.h"
#include "common/model.h"
#include "common/vector.h"

#include "game/g_entity.h"

extern g_entity_t cli_entities[G_ENTITIES_SIZE];
extern unsigned int cli_entity_count;

void cli_entities_init();
int cli_entity_add(const g_entity_t* entity);
int cli_entity_del(unsigned int i);

#endif /* __CLI_ENTITY_H__ */

/* EOF */
