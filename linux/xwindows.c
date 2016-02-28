/*
 * xwindows.c
 *
 * tudo relacionado ao X Windows System deve ser colocado aqui.
 *
 */

#if __DEBUG__
#include <stdio.h>
#include <assert.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <GL/glx.h>

#include "common/boolean.h"

#include "sys/sys_gl.h"
#include "sys/sys_input.h"

#include "sys/sys_common.h"
#include "sys/sys_env.h"
#include "sys/sys_event.h"

static enum
{
	INACTIVE =	0,
	INPUT =		1,
	OUTPUT =	2
} xwindows_state;

static Display* dpy = NULL;
static int screen = 0;
static Window win = 0;

static GLXContext ctx = NULL;

static const char* win_name = "Rogi's Engine =op";
static unsigned int win_w = 800, win_h = 600;
static int win_x = 0, win_y = 0;

static unsigned int m_x = 0, m_y = 0;
static bool m_grab = false;

static bool k_repeat = true;

static void xwindows_init();
static void xwindows_fini();
static void xwindows_getevents();

static void xwindows_init()
{
	Window root;

	int attr[] =
	{
		GLX_RGBA,
		GLX_RED_SIZE, 4,
		GLX_GREEN_SIZE, 4,
		GLX_BLUE_SIZE, 4,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE, 1,
		None
	};

	XVisualInfo* xvi;

	XSetWindowAttributes xswa;
	unsigned long int xswa_mask;

	XSizeHints sizehints;

#if __DEBUG__
	puts(_("starting xwindows subsystem."));
#endif

	dpy = XOpenDisplay(NULL);
	if(dpy == NULL)
	{
		xwindows_fini();
		sys_err(_("Could not open display."));
	}

	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);

	xvi = glXChooseVisual(dpy, screen, attr);
	if(xvi == NULL)
	{
		xwindows_fini();
		sys_err(_("Could not get a visual."));
	}

	xswa.colormap = XCreateColormap(dpy, root, xvi->visual, AllocNone);
	xswa.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask;

	xswa_mask = CWColormap | CWEventMask;

	win_x = 0;
	win_y = 0;

	/*
	win_w = sys_env_get("r_scenewidth");
	win_h = sys_env_get("r_sceneheight");
	win_h = sys_env_get("r_win_name");
	*/

	win_w = 800;
	win_h = 600;

	m_x = win_w / 2;
	m_y = win_h / 2;

	win = XCreateWindow(dpy, root, win_x, win_y, win_w, win_h, 0, xvi->depth, InputOutput, xvi->visual, xswa_mask, &xswa);

	XFreeColormap(dpy, xswa.colormap);

	sizehints.x = win_x;
	sizehints.y = win_y;
	sizehints.width  = win_w;
	sizehints.height = win_h;
	sizehints.flags = USSize | USPosition;
	XSetNormalHints(dpy, win, &sizehints);
	XSetStandardProperties(dpy, win, win_name, win_name, None, (char **)NULL, 0, &sizehints);

	ctx = glXCreateContext(dpy, xvi, NULL, true);
	if(ctx == NULL)
	{
		XFree(xvi);
		xwindows_fini();
		sys_err(_("Could not create a glX Context."));
	}

	XFree(xvi);

	XMapRaised(dpy, win);
	glXMakeCurrent(dpy, win, ctx);

//	XWarpPointer(dpy, None, win, 0, 0, 0, 0, 0, 0);
//	XWarpPointer(dpy, None, win, 0, 0, 0, 0, m_x, m_y);

	xwindows_getevents();
}

static void xwindows_fini()
{
#if __DEBUG__
	puts(_("finishing xwindows subsystem."));
#endif
	glXDestroyContext(dpy, ctx);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

static void xwindows_getevents()
{
	XEvent x_event;
	sys_event_t sys_event;

	long int m_rx, m_ry;
	unsigned int k;

	while(XPending(dpy) > 0)
	{
		XNextEvent(dpy, &x_event);
		switch(x_event.type)
		{
			case CreateNotify:
				win_x = x_event.xcreatewindow.x;
				win_y = x_event.xcreatewindow.y;
				win_w = x_event.xcreatewindow.width;
				win_h = x_event.xcreatewindow.height;

				sys_event.type = RESIZESCENE;
				sys_event.data.resizescene.width = win_w;
				sys_event.data.resizescene.height = win_h;
				sys_event_queue(&sys_event);
				break;

			case ConfigureNotify:
				win_x = x_event.xconfigure.x;
				win_y = x_event.xconfigure.y;
				win_w = x_event.xcreatewindow.width;
				win_h = x_event.xcreatewindow.height;

				sys_event.type = RESIZESCENE;
				sys_event.data.resizescene.width = win_w;
				sys_event.data.resizescene.height = win_h;
				sys_event_queue(&sys_event);
				break;

			case MotionNotify:
				m_rx = (signed int)x_event.xmotion.x - (signed int)m_x;
				m_ry = (signed int)x_event.xmotion.y - (signed int)m_y;
				m_x = x_event.xmotion.x;
				m_y = x_event.xmotion.y;

				if(m_grab)
				{
					/* descartar evento gerado pela centralização do mouse */
					if(m_x == win_w / 2 && m_y == win_h / 2)
						break;

					m_x = win_w / 2;
					m_y = win_h / 2;
					XWarpPointer(dpy, None, win, 0, 0, 0, 0, m_x, m_y);
				}

				sys_event.type = MOUSEMOTION;
				sys_event.data.mousemotion.x = m_x;
				sys_event.data.mousemotion.y = -m_y; /* normalmente y cresce para cima, mas para o X, y cresce para baixo. */
				sys_event.data.mousemotion.rx = m_rx;
				sys_event.data.mousemotion.ry = -m_ry; /* o mesmo para deslocamento relativo */
				sys_event_queue(&sys_event);
				break;

			case ButtonPress:
				k = x_event.xbutton.button;
				sys_event.type = BUTTONPRESS;
				sys_event.data.buttonpress.buttoncode = k;
				sys_event_queue(&sys_event);
				break;

			case ButtonRelease:
				k = x_event.xbutton.button;
				sys_event.type = BUTTONRELEASE;
				sys_event.data.buttonrelease.buttoncode = k;
				sys_event_queue(&sys_event);
				break;
			
			case KeyPress:
				k = x_event.xkey.keycode;
				sys_event.type = KEYPRESS;
				sys_event.data.keypress.keycode = k;
				sys_event_queue(&sys_event);
				break;
			
			case KeyRelease:
				k = x_event.xkey.keycode;
				sys_event.type = KEYRELEASE;
				sys_event.data.keyrelease.keycode = k;
				sys_event_queue(&sys_event);
				break;

			default:
				break;
		}
	}
}



void sys_gl_init()
{
#if __DEBUG__
	puts(_("starting opengl subsystem."));
#endif

	if(xwindows_state == INACTIVE)
		xwindows_init();

	xwindows_state = xwindows_state | OUTPUT;
}

void sys_gl_fini()
{
#if __DEBUG__
	puts(_("finishing opengl subsystem."));
#endif

	xwindows_state = xwindows_state ^ OUTPUT;

	if(xwindows_state == INACTIVE)
		xwindows_fini();
}

inline void sys_gl_swapbuffers()
{
	glXSwapBuffers(dpy, win);
}

inline void sys_gl_getsysevents()
{
	xwindows_getevents();
}

void sys_input_init()
{
#if __DEBUG__
	puts(_("starting input subsystem."));
#endif

	if(xwindows_state == INACTIVE)
		xwindows_init();

	xwindows_state = xwindows_state | INPUT;
}

void sys_input_fini()
{
#if __DEBUG__
	puts(_("finishing input subsystem."));
#endif

	xwindows_state = xwindows_state ^ INPUT;

	if(xwindows_state == INACTIVE)
		xwindows_fini();
}

inline void sys_input_getsysevents()
{
	xwindows_getevents();
}

inline unsigned int sys_input_keycode(char sym)
{
	return XKeysymToKeycode(dpy, sym);
}

inline char sys_input_keysym(unsigned int code)
{
	return XKeycodeToKeysym(dpy, code, 0);
}

inline void sys_input_toggleautorepeat()
{
	if(k_repeat)
		sys_input_autorepeatoff();

	else
		sys_input_autorepeaton();
}

inline void sys_input_autorepeaton()
{
	XAutoRepeatOn(dpy);
	k_repeat = true;
}

inline void sys_input_autorepeatoff()
{
	XAutoRepeatOff(dpy);
	k_repeat = false;
}

inline void sys_input_togglemousegrab()
{
	if(m_grab)
		sys_input_releasemouse();

	else
		sys_input_grabmouse();
}

inline void sys_input_grabmouse()
{
	if(!m_grab)
	{
		m_x = win_w / 2;
		m_y = win_h / 2;
		XWarpPointer(dpy, None, win, 0, 0, 0, 0, m_x, m_y);

		m_grab = true;
	}
}

inline void sys_input_releasemouse()
{
	if(m_grab)
		m_grab = false;
}

/* EOF */
