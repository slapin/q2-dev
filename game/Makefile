#
# Quake2 Makefile for Linux 2.0
#
# Nov '97 by Zoid <zoid@idsoftware.com>
#
# ELF only
#

# start of configurable options

# Here are your build options:
# (Note: not all options are available for all platforms).
# quake2 (uses OSS for sound, cdrom ioctls for cd audio) is automatically built.
# game$(ARCH).so is automatically built.
# Other compile-time options:
# Compile with IPv6 (protocol independent API). Tested on FreeBSD
HAVE_IPV6=NO

# (hopefully) end of configurable options

# Check OS type.
OSTYPE := $(shell uname -s)

# this nice line comes from the linux kernel makefile
ARCH := $(shell uname -m | sed -e s/i.86/i386/ -e s/sun4u/sparc/ -e s/sparc64/sparc/ -e s/arm.*/arm/ -e s/sa110/arm/ -e s/alpha/axp/)

CC=gcc

ifndef OPT_CFLAGS
ifeq ($(ARCH),axp)
OPT_CFLAGS=-ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations
endif

ifeq ($(ARCH),ppc)
OPT_CFLAGS=-O2 -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations
endif

ifeq ($(ARCH),sparc)
OPT_CFLAGS=-ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations
endif

ifeq ($(ARCH),i386)
OPT_CFLAGS=-O2 -ffast-math -funroll-loops -falign-loops=2 \
	-falign-jumps=2 -falign-functions=2 -fno-strict-aliasing
# compiler bugs with gcc 2.96 and 3.0.1 can cause bad builds with heavy opts.
#OPT_CFLAGS=-O6 -m486 -ffast-math -funroll-loops \
#	-fomit-frame-pointer -fexpensive-optimizations -malign-loops=2 \
#	-malign-jumps=2 -malign-functions=2
endif

ifeq ($(ARCH),x86_64)
#_LIB := 64
OPT_CFLAGS=-O2 -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations -fno-strict-aliasing
endif
endif
RELEASE_CFLAGS=$(BASE_CFLAGS) $(OPT_CFLAGS)

VERSION=3.21+r0.16

MOUNT_DIR=src

BUILD_DEBUG_DIR=debug$(ARCH)
BUILD_RELEASE_DIR=release$(ARCH)
CLIENT_DIR=$(MOUNT_DIR)/client
SERVER_DIR=$(MOUNT_DIR)/server
REF_SOFT_DIR=$(MOUNT_DIR)/ref_soft
REF_GL_DIR=$(MOUNT_DIR)/ref_gl
COMMON_DIR=$(MOUNT_DIR)/qcommon
LINUX_DIR=$(MOUNT_DIR)/linux
GAME_DIR=$(MOUNT_DIR)/game
CTF_DIR=$(MOUNT_DIR)/ctf
XATRIX_DIR=$(MOUNT_DIR)/xatrix
ROGUE_DIR=$(MOUNT_DIR)/rogue
NULL_DIR=$(MOUNT_DIR)/null

BASE_CFLAGS=-Wall -pipe -Dstricmp=strcasecmp
ifeq ($(HAVE_IPV6),YES)
BASE_CFLAGS+= -DHAVE_IPV6
ifeq ($(OSTYPE),FreeBSD)
BASE_CFLAGS+= -DHAVE_SIN6_LEN
endif
NET_UDP=net_udp6
else
NET_UDP=net_udp
endif

ifdef DEFAULT_BASEDIR
BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
endif
ifdef DEFAULT_LIBDIR
BASE_CFLAGS += -DDEFAULT_LIBDIR=\\\"$(DEFAULT_LIBDIR)\\\"
endif

ifeq ($(strip $(BUILD_QMAX)),YES)
	BASE_CFLAGS+=-DQMAX
endif

ifeq ($(strip $(BUILD_RETEXTURE)),YES)
	BASE_CFLAGS+=-DRETEX
endif

ifeq ($(strip $(BUILD_JOYSTICK)),YES)
BASE_CFLAGS+=-DJoystick
endif
ifeq ($(strip $(BUILD_ARTS)),YES)
BASE_CFLAGS+=$(shell artsc-config --cflags)
endif

ifneq ($(ARCH),i386)
 BASE_CFLAGS+=-DC_ONLY
endif

DEBUG_CFLAGS=$(BASE_CFLAGS) -g

ifeq ($(OSTYPE),FreeBSD)
LDFLAGS=-lm
endif
ifeq ($(OSTYPE),Linux)
LDFLAGS=-lm -ldl
endif

ifeq ($(strip $(BUILD_ARTS)),YES)
LDFLAGS+=$(shell artsc-config --libs)
endif

ifeq ($(strip $(BUILD_ALSA)),YES)
LDFLAGS+=-lasound
endif


SVGALDFLAGS=-lvga

XCFLAGS=-I/usr/X11R6/include
XLDFLAGS=-L/usr/X11R6/lib$(_LIB) -lX11 -lXext -lXxf86dga -lXxf86vm
AALDFLAGS=-lm -laa

SDLCFLAGS=$(shell sdl-config --cflags)
ifeq ($(strip $(STATICSDL)),YES)
	SDLLDFLAGS += -L/usr/X11R6/lib$(_LIB) -Wl,-Bstatic $(SDLDIR)/libSDL.a
	SDLLDFLAGS += $(SDLDIR)/libesd.a $(SDLDIR)/libartsc.a -Wl,-Bdynamic
	SDLLDFLAGS += -lpthread -lX11 -lXext -lXxf86dga -lXxf86vm -lXv \
		-lXinerama
else
	SDLLDFLAGS=$(shell sdl-config --libs)
endif

ifeq ($(strip $(BUILD_JOYSTICK)),YES)
SDLCFLAGS+=-DJoystick
endif

FXGLCFLAGS=-I/usr/X11R6/include
FXGLLDFLAGS=-L/usr/local/glide/lib -L/usr/X11/lib -L/usr/local/lib \
	-L/usr/X11R6/lib -lX11 -lXext -lGL -lvga

GLXCFLAGS=-I/usr/X11R6/include -DOPENGL
GLXLDFLAGS=-L/usr/X11R6/lib$(_LIB) -lX11 -lXext -lXxf86dga -lXxf86vm

SDLGLCFLAGS=$(SDLCFLAGS) -DOPENGL
SDLGLLDFLAGS=$(SDLLDFLAGS)

ifeq ($(strip $(BUILD_QMAX)),YES)
GLXLDFLAGS+=-ljpeg
SDLGLLDFLAGS+=-ljpeg
REF_GL_DIR = $(MOUNT_DIR)/ref_candygl
CL_FX = cl_fxmax.c
else
CL_FX = cl_fx.c
endif

SHLIBEXT=so

SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared

DO_CC=$(CC) $(CFLAGS) -o $@ -c $<
DO_DED_CC=$(CC) $(CFLAGS) -DDEDICATED_ONLY -o $@ -c $<
DO_DED_DEBUG_CC=$(CC) $(DEBUG_CFLAGS) -DDEDICATED_ONLY -o $@ -c $<
DO_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<
DO_GL_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) $(GLCFLAGS) -o $@ -c $<
DO_AS=$(CC) $(CFLAGS) -DELF -x assembler-with-cpp -o $@ -c $<
DO_SHLIB_AS=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -DELF -x assembler-with-cpp -o $@ -c $<

#############################################################################
# SETUP AND BUILD
#############################################################################

.PHONY : targets build_debug build_release clean clean-debug clean-release clean2 gamepack

TARGETS=$(BUILDDIR)/game$(ARCH).$(SHLIBEXT)

all: build_debug build_release gamepack

build_debug:
	@-mkdir -p $(BUILD_DEBUG_DIR) \
		$(BUILD_DEBUG_DIR)/game
	$(MAKE) targets BUILDDIR=$(BUILD_DEBUG_DIR) CFLAGS="$(DEBUG_CFLAGS) -DLINUX_VERSION='\"$(VERSION) Debug\"'"

build_release:
	@-mkdir -p $(BUILD_RELEASE_DIR) \
		$(BUILD_RELEASE_DIR)/game
	$(MAKE) targets BUILDDIR=$(BUILD_RELEASE_DIR) CFLAGS="$(RELEASE_CFLAGS) -DLINUX_VERSION='\"$(VERSION)\"'"

gamepack:
	$(MAKE) -C scripts

targets: $(TARGETS)

#############################################################################
# GAME
#############################################################################

GAME_OBJS = \
	$(BUILDDIR)/game/g_ai.o \
	$(BUILDDIR)/game/p_client.o \
	$(BUILDDIR)/game/g_chase.o \
	$(BUILDDIR)/game/g_cmds.o \
	$(BUILDDIR)/game/g_svcmds.o \
	$(BUILDDIR)/game/g_combat.o \
	$(BUILDDIR)/game/g_func.o \
	$(BUILDDIR)/game/g_items.o \
	$(BUILDDIR)/game/g_main.o \
	$(BUILDDIR)/game/g_misc.o \
	$(BUILDDIR)/game/g_monster.o \
	$(BUILDDIR)/game/g_phys.o \
	$(BUILDDIR)/game/g_save.o \
	$(BUILDDIR)/game/g_spawn.o \
	$(BUILDDIR)/game/g_target.o \
	$(BUILDDIR)/game/g_trigger.o \
	$(BUILDDIR)/game/g_turret.o \
	$(BUILDDIR)/game/g_utils.o \
	$(BUILDDIR)/game/g_weapon.o \
	$(BUILDDIR)/game/m_actor.o \
	$(BUILDDIR)/game/m_berserk.o \
	$(BUILDDIR)/game/m_boss2.o \
	$(BUILDDIR)/game/m_boss3.o \
	$(BUILDDIR)/game/m_boss31.o \
	$(BUILDDIR)/game/m_boss32.o \
	$(BUILDDIR)/game/m_brain.o \
	$(BUILDDIR)/game/m_chick.o \
	$(BUILDDIR)/game/m_flipper.o \
	$(BUILDDIR)/game/m_float.o \
	$(BUILDDIR)/game/m_flyer.o \
	$(BUILDDIR)/game/m_gladiator.o \
	$(BUILDDIR)/game/m_gunner.o \
	$(BUILDDIR)/game/m_hover.o \
	$(BUILDDIR)/game/m_infantry.o \
	$(BUILDDIR)/game/m_insane.o \
	$(BUILDDIR)/game/m_medic.o \
	$(BUILDDIR)/game/m_move.o \
	$(BUILDDIR)/game/m_mutant.o \
	$(BUILDDIR)/game/m_parasite.o \
	$(BUILDDIR)/game/m_soldier.o \
	$(BUILDDIR)/game/m_supertank.o \
	$(BUILDDIR)/game/m_tank.o \
	$(BUILDDIR)/game/p_hud.o \
	$(BUILDDIR)/game/p_trail.o \
	$(BUILDDIR)/game/p_view.o \
	$(BUILDDIR)/game/p_weapon.o \
	$(BUILDDIR)/game/q_shared.o \
	$(BUILDDIR)/game/m_flash.o

$(BUILDDIR)/game$(ARCH).$(SHLIBEXT) : $(GAME_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(GAME_OBJS)

$(BUILDDIR)/game/g_ai.o :        $(GAME_DIR)/g_ai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_chase.o :     $(GAME_DIR)/g_chase.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_client.o :    $(GAME_DIR)/p_client.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_cmds.o :      $(GAME_DIR)/g_cmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_svcmds.o :    $(GAME_DIR)/g_svcmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_combat.o :    $(GAME_DIR)/g_combat.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_func.o :      $(GAME_DIR)/g_func.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_items.o :     $(GAME_DIR)/g_items.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_main.o :      $(GAME_DIR)/g_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_misc.o :      $(GAME_DIR)/g_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_monster.o :   $(GAME_DIR)/g_monster.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_phys.o :      $(GAME_DIR)/g_phys.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_save.o :      $(GAME_DIR)/g_save.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_spawn.o :     $(GAME_DIR)/g_spawn.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_target.o :    $(GAME_DIR)/g_target.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_trigger.o :   $(GAME_DIR)/g_trigger.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_turret.o :    $(GAME_DIR)/g_turret.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_utils.o :     $(GAME_DIR)/g_utils.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_weapon.o :    $(GAME_DIR)/g_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_actor.o :     $(GAME_DIR)/m_actor.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_berserk.o :   $(GAME_DIR)/m_berserk.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss2.o :     $(GAME_DIR)/m_boss2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss3.o :     $(GAME_DIR)/m_boss3.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss31.o :     $(GAME_DIR)/m_boss31.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss32.o :     $(GAME_DIR)/m_boss32.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_brain.o :     $(GAME_DIR)/m_brain.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_chick.o :     $(GAME_DIR)/m_chick.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_flipper.o :   $(GAME_DIR)/m_flipper.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_float.o :     $(GAME_DIR)/m_float.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_flyer.o :     $(GAME_DIR)/m_flyer.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_gladiator.o : $(GAME_DIR)/m_gladiator.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_gunner.o :    $(GAME_DIR)/m_gunner.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_hover.o :     $(GAME_DIR)/m_hover.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_infantry.o :  $(GAME_DIR)/m_infantry.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_insane.o :    $(GAME_DIR)/m_insane.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_medic.o :     $(GAME_DIR)/m_medic.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_move.o :      $(GAME_DIR)/m_move.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_mutant.o :    $(GAME_DIR)/m_mutant.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_parasite.o :  $(GAME_DIR)/m_parasite.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_soldier.o :   $(GAME_DIR)/m_soldier.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_supertank.o : $(GAME_DIR)/m_supertank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_tank.o :      $(GAME_DIR)/m_tank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_hud.o :       $(GAME_DIR)/p_hud.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_trail.o :     $(GAME_DIR)/p_trail.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_view.o :      $(GAME_DIR)/p_view.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_weapon.o :    $(GAME_DIR)/p_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/q_shared.o :    $(GAME_DIR)/q_shared.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_flash.o :     $(GAME_DIR)/m_flash.c
	$(DO_SHLIB_CC)


clean: clean-debug clean-release clean-gamepack

clean-debug:
	$(MAKE) clean2 BUILDDIR=$(BUILD_DEBUG_DIR) CFLAGS="$(DEBUG_CFLAGS)"

clean-release:
	$(MAKE) clean2 BUILDDIR=$(BUILD_RELEASE_DIR) CFLAGS="$(DEBUG_CFLAGS)"

clean-gamepack:
	$(MAKE) -C scripts clean

clean2:
	rm -f \
	$(GAME_OBJS) \

distclean:
	@-rm -rf $(BUILD_DEBUG_DIR) $(BUILD_RELEASE_DIR)
	@-rm -f `find . \( -not -type d \) -and \
		\( -name '*~' \) -type f -print`
