/*
 * sys_env.c
 *
 * variaveis de ambiente
 *
 */

#include <string.h>

#include "sys/sys_env.h"

static sys_var_t env[SYS_ENV_SIZE];
static unsigned long int sys_env_count = 0;

static sys_var_t* sys_env_find_unused(const char* name)
{
	unsigned long int i;
	for(i = 0; i < SYS_ENV_SIZE; i++)
	{
		if(env[i].name[0] == '\0')
			return &env[i];
	}

	return NULL;
}

static sys_var_t* sys_env_find(const char* name)
{
	unsigned long int i;
	for(i = 0; i < SYS_ENV_SIZE; i++)
	{
		if(strcmp(name, env[i].name) == 0)
			return &env[i];
	}

	return NULL;
}

void sys_env_init()
{
	memset(env, 0, sizeof(sys_var_t) * SYS_ENV_SIZE);
}

void sys_env_fini()
{
}

int sys_env_unset(const char* name)
{
	sys_var_t* var;
	var = sys_env_find(name);

	if(var == NULL)
		return -1;

	memset(var, 0, sizeof(sys_var_t));
	sys_env_count--;
	return 0;
}

int sys_env_set(const char* name, const char* value)
{
	sys_var_t* var;
	var = sys_env_find(name);

	if(var == NULL) /* nova variavel */
	{
		var = sys_env_find_unused(name);
		if(var == NULL) /* limite de variaveis atingido */
			return -1;

		sys_env_count++;
	}

	strncpy(var->name, name, VAR_NAME_SIZE);
	strncpy(var->value, value, VAR_VALUE_SIZE);
	return 0;
}

const char* sys_env_get(const char* name)
{
	sys_var_t* var;
	var = sys_env_find(name);

	if(var == NULL)
		return NULL;

	return var->value;
}

/* EOF */

