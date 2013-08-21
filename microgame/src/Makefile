DO_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<
DO_SHLIB_AS=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -DELF -x assembler-with-cpp -o $@ -c $<
# this nice line comes from the linux kernel makefile
ARCH := $(shell uname -m | sed -e s/i.86/i386/ -e s/sun4u/sparc/ -e s/sparc64/sparc/ -e s/arm.*/arm/ -e s/sa110/arm/ -e s/alpha/axp/)
SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared
SHLIBEXT=so
CFLAGS=-g -O2 -fno-omit-frame-pointer -Wall

all: game$(ARCH).$(SHLIBEXT)

SRCS = microgame.c
OBJS = $(SRCS:.c=.o)

game$(ARCH).$(SHLIBEXT): $(OBJS)
	 $(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(DO_SHLIB_CC)

clean:
	rm -f $(OBJS) game$(ARCH).$(SHLIBEXT)

.PHONY: clean
