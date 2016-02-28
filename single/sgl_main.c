/*
 * sgl_main.c
 *
 * rotina principal do single player
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <math.h>

#include "common/vector.h"
#include "common/mathconstants.h"

#include "sys/sys_common.h"
#include "sys/sys_time.h"
#include "sys/sys_env.h"
#include "sys/sys_event.h"

#include "sys/sys_gl.h"
#include "sys/sys_input.h"

#include "renderer/renderer.h"
#include "renderer/r_bsp.h"
#include "renderer/r_g_entity.h"

#include "rogimodel/rogimodel.h"

#include "bsp/bsp.h"

#include "game/g_entity.h"
#include "game/g_main.h"
#include "game/g_map.h"

#include "single/sgl_main.h"

static vec3_t eye_src = {0, 0, 5};
static vec3_t eye_rot = {0, 0, 0};

static bool move_forward =	false,
	    move_backward =	false,
	    move_left =		false,
	    move_right =	false;

static bool mouselook = false;

static double sensitivity = 0.5;
static double movespeed = 2;

static sys_time_t lastframetime = -1;

static bool done = false;

void sgl_init()
{
	sys_env_init();
	sys_event_init();

	sys_gl_init();
	sys_input_init();

	r_init();

	g_init();
}

void sgl_fini()
{
	g_fini();

	r_fini();

	sys_input_fini();
	sys_gl_fini();

	sys_event_fini();
	sys_env_fini();
}

void shoot(const vec3_t src, const vec3_t dir, const model_t* model)
{
	vec3_copy(g_entities[0].src, eye_src);
	vec3_copy(g_entities[0].dir, dir);
	g_entities[0].speed = 10;
}

void sgl_frame()
{
	bool should_shoot = false;

	sys_time_t time, timepassed;
	time = sys_time();
	timepassed = time - lastframetime;

	/*
	 * input
	 *
	 */
	sys_gl_getsysevents();
	sys_input_getsysevents();

	while(sys_event_pending() > 0)
	{
		sys_event_t event;
		sys_event_next(&event);

		switch(event.type)
		{
			case RESIZESCENE:
				r_resizescene(event.data.resizescene.width, event.data.resizescene.height);
				break;

			case KEYPRESS:
				switch(sys_input_keysym(event.data.keypress.keycode))
				{
					case 'q':
						done = true;
						return;

					case 'm':
						sys_input_togglemousegrab();
						mouselook = !mouselook;

						break;

					case 'w':
						move_forward = true;
						break;

					case 's':
						move_backward = true;
						break;

					case 'a':
						move_left = true;
						break;

					case 'd':
						move_right = true;
						break;
							
					default:
						break;
				}
				break;

			case KEYRELEASE:
				switch(sys_input_keysym(event.data.keyrelease.keycode))
				{
					case 'w':
						move_forward = false;
						break;

					case 's':
						move_backward = false;
						break;

					case 'a':
						move_left = false;
						break;

					case 'd':
						move_right = false;
						break;

					case 'x':
						should_shoot = true;
						break;
							
					default:
						break;
				}
				break;

			case MOUSEMOTION:
				if(mouselook)
				{
					eye_rot[1] -= (double)event.data.mousemotion.rx * sensitivity;
					eye_rot[0] -= (double)-event.data.mousemotion.ry * sensitivity;
					if(eye_rot[0] > 90)
						eye_rot[0] = 90;

					if(eye_rot[0] < -90)
						eye_rot[0] = -90;
					
				}
				break;

			default:
				break;
		}
	}

	static vec3_t dir;
	dir[0] = -sin(eye_rot[1] * M_PI / 180);
	dir[1] = 0;
	dir[2] = -cos(eye_rot[1] * M_PI / 180);
	vec3_normalize(dir, dir);

	

	if(should_shoot)
	{
		shoot(eye_src, dir, g_entities[0].model);
		should_shoot = false;
	}

	if(move_left)
	{
		vec3_t dest, y, dg;
		vec3_init(y, 0, 1, 0);
		vec3_init(dg, dir[0], 0, dir[2]);
		vec3_crossproduct(dest, y, dg);
		vec3_normalize(dest, dest);
		vec3_scale(dest, dest, timepassed * movespeed);
		vec3_add(eye_src, eye_src, dest);
	}

	if(move_right)
	{
		vec3_t dest, y, dg;
		vec3_init(y, 0, 1, 0);
		vec3_init(dg, dir[0], 0, dir[2]);
		vec3_crossproduct(dest, y, dg);
		vec3_normalize(dest, dest);
		vec3_scale(dest, dest, timepassed * -movespeed);
		vec3_add(eye_src, eye_src, dest);
	}

	if(move_forward)
	{
		vec3_t dest;
		vec3_scale(dest, dir, timepassed * movespeed);
		vec3_add(eye_src, eye_src, dest);
	}

	if(move_backward)
	{
		vec3_t dest;
		vec3_scale(dest, dir, timepassed * -movespeed);
		vec3_add(eye_src, eye_src, dest);
	}

	/*
	 * game
	 *
	 */
	g_frame();

	/*
	 * ajusta camera
	 *
	 */
	glLoadIdentity();
	glRotated(-eye_rot[0], 1, 0, 0);
	glRotated(-eye_rot[1], 0, 1, 0);
	glRotated(-eye_rot[2], 0, 0, 1);
	glTranslated(-eye_src[0], -eye_src[1], -eye_src[2]);

	/*
	 * FIXME: luz
	 *
	 */
	fvec4_t light_pos = {30, 0, 0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	/*
	 * desenha mapa
	 *
	 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	r_render_bsp_tree(&g_map, eye_src);

	/*
	 * desenha entidades
	 *
	 */

	unsigned int i;
	for(i = 0; i < G_ENTITIES_SIZE; i++)
	{
		if(g_entities[i].active)
		{
			r_render_g_entity(&g_entities[i]);
		}
	}

	sys_gl_swapbuffers();

#if __DEBUG__
//	printf("                    \rfps = %lf\r", (double)1 / timepassed);
#endif
	lastframetime = time;
}

void sgl_frame_sync()
{
	lastframetime = sys_time();
}

void sgl_run()
{
	sgl_init();

	/*
	 * objetos da cena
	 *
	 */
	g_entity_t monkey =
	{
		false,		/* active */
		0,		/* i */

//		{3, 0, 0},	/* src */
		{0, 0, 10},
		{1, 1, 1},	/* scale */
		{0, 0, 0},	/* rot */


		{0, 0, 0},	/* dir */

		1,		/* speed */

		{0, 0, 0},	/* bbsrc */
		{0, 0, 0},	/* bbsize */

		NULL		/* model */
	};

	vec3_normalize(monkey.dir, monkey.dir);

	monkey.model = malloc(sizeof(model_t));
	rogimodel_read(monkey.model, "purple_monkey.r3m");

	g_entity_add(&monkey);
	g_map_load("green_tube.bsp");

//	fvec4_t ambient_light = {0, 0, 0, 1};
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	fvec4_t light_color = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
	glEnable(GL_LIGHT0);

	/*
	 * Ajusta posição inicial de desenho
	 *
	 */
	glMatrixMode(GL_MODELVIEW);
//	glPolygonMode(GL_FRONT, GL_LINE);
//	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
//	glShadeModel(GL_FLAT);

	/*
	 * Entra no loop de frames
	 *
	 */

	sys_input_autorepeatoff();

	g_frame_sync();
	while(!done)
		sgl_frame();

	sys_input_autorepeaton();
	sgl_fini();
}	

/* EOF */
