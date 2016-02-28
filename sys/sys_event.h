/*
 * sys_event.h
 *
 * lida com eventos do sistema
 *
 */

#ifndef __SYS_EVENT_H__
#define __SYS_EVENT_H__ 1

#include "sys/sys_time.h"

typedef enum sys_event_type_e
{
	RESIZESCENE,
	KEYPRESS,
	KEYRELEASE,
	BUTTONPRESS,
	BUTTONRELEASE,
	MOUSEMOTION
} sys_event_type_t;

typedef struct sys_event_resizescene_s
{
	unsigned int width, height;
} sys_event_resizescene_t;

typedef struct sys_event_keypress_s
{
	unsigned int keycode;
} sys_event_keypress_t, sys_event_keyrelease_t;

typedef struct sys_event_buttonpress_s
{
	unsigned long int buttoncode;
} sys_event_buttonpress_t, sys_event_buttonrelease_t;

typedef struct sys_event_mousemotion_s
{
	unsigned long int x, y;
	long int rx, ry;
} sys_event_mousemotion_t;

typedef struct sys_event_s
{
	sys_event_type_t type;
	sys_time_t time;

	union
	{
		sys_event_resizescene_t resizescene;
		sys_event_keypress_t keypress;
		sys_event_keyrelease_t keyrelease;
		sys_event_buttonpress_t buttonpress;
		sys_event_buttonrelease_t buttonrelease;
		sys_event_mousemotion_t mousemotion;
	} data;
} sys_event_t;

void sys_event_init();
void sys_event_fini();
inline unsigned int sys_event_pending();
inline int sys_event_next(sys_event_t* event);
inline int sys_event_queue(const sys_event_t* event);

#endif /* __SYS_EVENT_H__ */

/* EOF */
