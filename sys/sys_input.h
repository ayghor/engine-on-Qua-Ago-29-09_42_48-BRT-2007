/*
 * sys_input.h
 *
 * rotinas dependentes de implementação relativas à entrada de dados por 
 * teclado mouse e joystick
 *
 */

#ifndef __SYS_INPUT_H__
#define __SYS_INPUT_H__ 1

void sys_input_init();
void sys_input_fini();
inline void sys_input_getsysevents();
inline unsigned int sys_input_keycode(char sym);
inline char sys_input_keysym(unsigned int code);
inline void sys_input_toggleautorepeat();
inline void sys_input_autorepeaton();
inline void sys_input_autorepeatoff();
inline void sys_input_togglemousegrab();
inline void sys_input_grabmouse();
inline void sys_input_releasemouse();

#endif /* __SYS_INPUT_H__ */

/* EOF */
