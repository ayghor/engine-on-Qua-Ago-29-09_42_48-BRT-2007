/*
 * g_main.c
 *
 * rotina principal do jogo
 *
 */

#if __DEBUG__
#include <stdio.h>
#endif

#include "sys/sys_common.h"
#include "sys/sys_time.h"
#include "sys/sys_env.h"

#include "trace/tr_bsp.h"

#include "game/g_entity.h"
#include "game/g_map.h"

extern vec3_t eye_src;

static sys_time_t lastframetime = -1;

/*
 * g_init()
 *
 * Inicia o modulo game.
 *
 */
void g_init()
{
	g_entities_init();
}

/*
 * g_fini()
 *
 * Finaliza o modulo game.
 *
 */
void g_fini()
{
	g_entities_fini();
}

/*
 * g_frame()
 *
 * Essa função é responsavel por avançar as entidades no tempo.
 *
 */
void g_frame()
{
	sys_time_t time, timepassed;
	time = sys_time();
	timepassed = time - lastframetime;

	/*
	 * entidades
	 *
	 */
	unsigned long int i;
	for(i = 0; i < G_ENTITIES_SIZE; i++)
	{
		if(g_entities[i].active)
		{
			vec_t moveleft = g_entities[i].speed * timepassed;

			/*
			 * colisões contra entidades
			 *
			 */

			/* FIXME */				

			/*
			 * colisoes contra mapa
			 *
			 */
#if 0
			while(moveleft > 0)
			{
				const bsp_node_t* rnode;
				vec3_t r;
				vec_t t = moveleft;
				bool collided = false;
	
				tr_trace_vs_bsp_node(g_entities[i].src, g_entities[i].dir, &g_map.root, &collided, &rnode, r, &t);

				if(collided)
				{
					vec3_copy(g_entities[i].src, r);
					vec3_reflect(g_entities[i].dir, g_entities[i].dir, rnode->normal);
					vec3_normalize(g_entities[i].dir, g_entities[i].dir);

					moveleft -= t;
					continue;
				}

				vec3_t desloc;
				vec3_scale(desloc, g_entities[i].dir, t);
				vec3_add(g_entities[i].src, g_entities[i].src, desloc);
				moveleft -= t;
			}
#endif

			while(moveleft > 0)
			{
				const bsp_node_t* rnode;
				vec3_t r;
				vec_t t;
				bool collided;

				t = moveleft;
				collided = false;

				tr_trace_vs_bsp_node(g_entities[i].src, g_entities[i].dir, &g_map.root, &collided, &rnode, r, &t);

				if(collided)
				{
					vec3_reflect(g_entities[i].dir, g_entities[i].dir, rnode->normal);
					vec3_normalize(g_entities[i].dir, g_entities[i].dir);
				}

				else
				{
					vec3_scale(r, g_entities[i].dir, moveleft);
					vec3_add(r, r, g_entities[i].src);
				}

				vec3_copy(g_entities[i].src, r);
				moveleft -= t;
			}
		}
	}

	lastframetime = time;
}

void g_frame_sync()
{
	lastframetime = sys_time();
}

/* EOF */
