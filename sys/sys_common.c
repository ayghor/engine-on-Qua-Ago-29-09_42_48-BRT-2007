/*
 * sys_common.c
 *
 * funções comuns
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#if __DEBUG__
#include <assert.h>
#endif

#include "sys/sys_common.h"

#define SYS_ERRMSG	"***Error: "
#define SYS_WARNMSG	"***Warning: "

void sys_err(const char* format, ...)
{
	va_list ap;
	
	fputs(_(SYS_ERRMSG), stderr);

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fputc('\n', stderr);
	sys_exit(-1);
}

void sys_warn(const char* format, ...)
{
	va_list ap;
	
	fputs(_(SYS_WARNMSG), stderr);

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fputc('\n', stderr);
}

void sys_exit(int r)
{
	if(r != 0)
		abort();

	exit(r);
}

/* EOF */
