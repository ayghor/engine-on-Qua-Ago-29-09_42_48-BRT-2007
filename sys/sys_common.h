/*
 * sys_common.h
 *
 * funções comuns
 *
 */

#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__ 1

void sys_err(const char* format, ...);
void sys_warn(const char* format, ...);
void sys_exit(int r);

#define _(s) ((s))

#endif /* __SYS_COMMON_H__ */

/* EOF */
