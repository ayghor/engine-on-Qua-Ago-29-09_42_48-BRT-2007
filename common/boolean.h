/*
 * boolean.h
 *
 * tipo booleano e macros
 *
 */

#ifndef __BOOLEAN_H__
#define __BOOLEAN_H__ 1

#if __linux__
#include <stdbool.h>

#else
typedef unsigned char bool;

#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif

#endif /* !__linux__ */

#endif /* __BOOLEAN_H__ */

/* EOF */
