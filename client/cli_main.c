/*
 * cli_main.c
 *
 * rotina principal do cliente
 *
 * tudo relativo a entidades pertence a esse modulo
 *
 */

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "common/boolean.h"

#include "sys/sys_common.h"
#include "sys/sys_time.h"
#include "sys/sys_event.h"
#include "sys/sys_env.h"

#include "sys/sys_gl.h"
#include "sys/sys_input.h"

#include "game/g_main.h"
#include "game/g_entity.h"

#include "renderer/renderer.h"
#include "renderer/r_model.h"

#include "rogimodel/rogimodel.h"

static sys_time_t lastframetime = -1;

void g_init()
{
	sys_env_init();
	sys_event_init();
	sys_gl_init();
	sys_input_init();
	g_entities_init();

	r_gl_init();
	r_gl_resizescene(800, 600);

	glClearColor(1, 1, 1, 1);
	glClearDepth(1);

	glLoadIdentity();
	glTranslated(0, 0, -10);

	fvec4_t light_pos;
	fvec4_init(light_pos, 5, 5, 10, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glEnable(GL_LIGHT0);

	g_entity_t ent;
	memset(&ent, 0, sizeof(g_entity_t));
	ent.model = malloc(sizeof(model_t));
	rogimodel_read(ent.model, "cubo_vermelho.r3m");
	vec3_init(ent.scale, 1, 1, 1);
	g_entity_add(&ent);
}

void g_fini()
{
	sys_input_fini();
	sys_gl_fini();
	sys_event_fini();
	sys_env_fini();
}

inline void g_frame_sync()
{
	lastframetime = -1;
}

void g_frame()
{
	sys_time_t time, timepassed;

	time = sys_time();

	if(lastframetime < 0)
		lastframetime = time;

	timepassed = time - lastframetime;

	sys_gl_getsysevents();
	sys_input_getsysevents();
		
	while(sys_event_pending() > 0)
	{
		sys_event_t event;
		sys_event_next(&event);

		switch(event.type)
		{
			case RESIZESCENE:
				r_gl_resizescene(event.data.resizescene.width, event.data.resizescene.height);
				break;

			case KEYPRESS:
				switch(sys_input_keysym(event.data.keypress.keycode))
				{
					case 'q':
						g_fini();
						sys_exit(0);

					case 'm':
						sys_input_togglemousegrab();
						break;
							
					default:
						break;
				}
				break;

			case MOUSEMOTION:
				break;

			default:
				break;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	unsigned int i;
	for(i = 0; i < G_ENTITIES_SIZE; i++)
	{
		if(g_entities[i].active)
			g_gl_draw_entity(&g_entities[i]);
	}

	sys_gl_swapbuffers();
	lastframetime = time;
}

/* EOF */
