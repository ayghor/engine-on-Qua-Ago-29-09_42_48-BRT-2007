/*
 * env.h
 *
 * variaveis de ambiente
 *
 */

#ifndef __SYS_ENV_H__
#define __SYS_ENV_H__ 1

#define VAR_NAME_SIZE	256
#define VAR_VALUE_SIZE	1024

#define SYS_ENV_SIZE	1024

typedef struct sys_var_s
{
	char name[VAR_NAME_SIZE];
	char value[VAR_VALUE_SIZE];
} sys_var_t;

void sys_env_init();
void sys_env_fini();
int sys_env_unset(const char* name);
int sys_env_set(const char* name, const char* value);
const char* sys_env_get(const char* name);

#endif /* __SYS_ENV_H__ */

/* EOF */
