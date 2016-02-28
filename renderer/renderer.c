/*
 * renderer.c
 *
 * desenha entidades
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer.h"

void r_init()
{
//	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_FOG_HINT, GL_NICEST);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);

	glClearColor(1, 1, 1, 1);
	glClearDepth(1);

	glShadeModel(GL_SMOOTH);

//	glPolygonMode(GL_FRONT, GL_FILL);
//	glPolygonMode(GL_FRONT, GL_LINE);
//	glPolygonMode(GL_FRONT, GL_POINT);
//	glPolygonMode(GL_BACK, GL_FILL);
//	glPolygonMode(GL_BACK, GL_LINE);
//	glPolygonMode(GL_BACK, GL_POINT);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

//	glEnable(GL_FOG);
	glEnable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_ONE, GL_ZERO);
	glEnable(GL_BLEND);
	
	glEnable(GL_TEXTURE_2D);
}

void r_fini()
{
	return;
}

void r_resizescene(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)width/(double)height, 1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void r_renderer()
{
	/* do stuff */
	return;
}

void r_render_map()
{
	/* do stuff */
	return;
}

/* EOF */
