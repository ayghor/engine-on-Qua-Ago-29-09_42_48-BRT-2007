####
#
# Rogi Engine Makefile
#
# rogi <rogi@linuxmail.org>
#

##
# Configurações do compilador fornecidas pelo usuário
# 
CC =			gcc
CFLAGS =		-g -Wall -D__DEBUG__
LDFLAGS =
##

##
# Configurações finais do compilador
#
BUILD_CC =		$(CC)
BUILD_CFLAGS =		-Dinline='' -ggdb -std=c99 -pedantic -fPIC -I$(CURDIR) $(CFLAGS)
BUILD_LDFLAGS =		$(LDFLAGS)
##

##
# Configurações de pacotes externos
#
##

##
# INCLUDE
#
##

##
# LINK
#
LINK_PTHREAD =		-lpthread
LINK_MATH =		-lm
LINK_X =		-L/usr/X11R7/lib64 -lX11
LINK_GL =		-L/usr/lib64 -lGL -lGLU
LINK_CURSES =		-lcurses
LINK_READLINE =		$(LINK_CURSES) -lreadline $(LINK_CURSES)
##

##
# Lista de alvos
#

BSP_OBJS= \
bsp/bsp.o \
bsp/bsp_model.o

CLIENT_OBJS= \
client/cli_main.o \
client/cli_entity.o

COMMON_OBJS= \
common/vector.o

GAME_OBJS= \
game/g_main.o \
game/g_entity.o \
game/g_map.o

GRAPHICS_OBJS= \
graphics/image.o \
graphics/model.o

LINUX_OBJS= \
linux/system.o \
linux/time.o \
linux/xwindows.o

RENDERER_OBJS= \
renderer/renderer.o \
renderer/r_model.o \
renderer/r_bsp.o \
renderer/r_g_entity.o

ROGIMODEL_OBJS= \
rogimodel/rogimodel.o

SINGLE_OBJS= \
single/sgl_main.o

SYS_OBJS= \
sys/sys_event.o \
sys/sys_console.o \
sys/sys_env.o \
sys/sys_common.o

TRACE_OBJS= \
trace/tr_bsp.o \
trace/tr_model.o \
trace/trace.o

PROG_OBJS= \
bspc.o \
sgl.o

PROGS= \
bspc \
sgl

OBJS= $(BSP_OBJS) $(TRACE_OBJS) $(COMMON_OBJS) $(GAME_OBJS) $(GRAPHICS_OBJS) $(LINUX_OBJS) $(RENDERER_OBJS) $(ROGIMODEL_OBJS) $(SINGLE_OBJS) $(SYS_OBJS) 

BSPC_OBJS= $(BSP_OBJS) $(TRACE_OBJS) $(COMMON_OBJS) $(GRAPHICS_OBJS) $(ROGIMODEL_OBJS)

ALL_OBJS= $(OBJS) $(PROG_OBJS)

##

##
# Alvos
#
# Pseudo-alvos
.PHONY: all clean

# Compila todos os programas e livrarias
all: sgl bspc

clean:
	rm -f $(ALL_OBJS) $(PROGS)

$(ALL_OBJS):
	$(BUILD_CC) $(BUILD_CFLAGS) -c -o $@ $(@:.o=.c)

sgl: sgl.o $(OBJS)
	$(BUILD_CC) $(BUILD_CFLAGS) -o sgl $^ $(LINK_MATH) $(LINK_X) $(LINK_GL)

bspc: bspc.o $(BSPC_OBJS)
	$(BUILD_CC) $(BUILD_CFLAGS) -o bspc $^ $(LINK_MATH) $(LINK_X) $(LINK_GL)

# EOF
