/*
 * sys_time.h
 *
 * funções para medir tempo
 *
 */

#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__ 1

typedef double sys_time_t;

void sys_sleep(sys_time_t time);
sys_time_t sys_time();

#endif /* __SYS_TIME_H__ */

/* EOF */
