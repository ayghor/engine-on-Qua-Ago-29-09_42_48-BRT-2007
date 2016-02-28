/*
 * sys_gl.h
 *
 * rotinas dependentes de implementação relativas ao opengl
 *
 */

#ifndef __SYS_GL_H__
#define __SYS_GL_H__ 1

void sys_gl_init();
void sys_gl_fini();
inline void sys_gl_swapbuffers();
inline void sys_gl_getsysevents();

#endif /* __SYS_GL_H__ */

/* EOF */
