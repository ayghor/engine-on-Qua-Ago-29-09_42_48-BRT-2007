/*
 * sys_event.c
 *
 * lida com eventos do sistema
 *
 */

#include <string.h>

#include "sys/sys_event.h"

#define SYS_EVENT_QUEUE_SIZE 256

static sys_event_t queue[SYS_EVENT_QUEUE_SIZE];
static unsigned int current = 0;
static unsigned int last = SYS_EVENT_QUEUE_SIZE - 1;
static unsigned int pending = 0;

void sys_event_init()
{
	current = 0;
	pending = 0;
}

void sys_event_fini()
{
}

inline unsigned int sys_event_pending()
{
	return pending;
}

inline int sys_event_next(sys_event_t* event)
{
	memcpy(event, &queue[current], sizeof(sys_event_t));

	if(pending < 1)
		return -1;

	if(current == SYS_EVENT_QUEUE_SIZE - 1)
		current = 0;

	else
		current++;

	pending--;
	return 0;
}

inline int sys_event_queue(const sys_event_t* event)
{
	if(pending == SYS_EVENT_QUEUE_SIZE)
		return -1;

	if(last == SYS_EVENT_QUEUE_SIZE - 1)
		last = 0;

	else
		last++;

	memcpy(&queue[last], event, sizeof(sys_event_t));
	pending++;
	return 0;
}

/* EOF */
