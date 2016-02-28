/*
 * time.c
 *
 * funções para medir tempo
 *
 */

#define _POSIX_C_SOURCE 199309
//#define __USE_POSIX199309 1
#include <time.h>
//#undef __USE_POSIX199309

#include <sys/time.h>

#include "sys/sys_time.h"

void sys_sleep(sys_time_t time)
{
	struct timespec ts;
	ts.tv_sec = time;
	ts.tv_nsec = (time - ts.tv_sec) * 1000000000;

	nanosleep(&ts, NULL);
}

sys_time_t sys_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return (sys_time_t)tv.tv_sec + (sys_time_t)tv.tv_usec / 1000000;
}

/* EOF */
