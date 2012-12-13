
bspinfo3_SRCS = bsp/bspinfo3/bspinfo3.c
bspinfo3_OBJS =$(bspinfo3_SRCS:.c=.o)

qbsp3_SRCS = bsp/qbsp3/brushbsp.c bsp/qbsp3/csg.c bsp/qbsp3/faces.c \
	bsp/qbsp3/glfile.c bsp/qbsp3/leakfile.c bsp/qbsp3/map.c bsp/qbsp3/nodraw.c \
	bsp/qbsp3/portals.c bsp/qbsp3/prtfile.c bsp/qbsp3/qbsp3.c bsp/qbsp3/textures.c \
	bsp/qbsp3/tree.c bsp/qbsp3/writebsp.c

qrad3_SRCS = bsp/qrad3/lightmap.c bsp/qrad3/patches.c bsp/qrad3/qrad3.c \
	bsp/qrad3/trace.c

qvis3_SRCS = bsp/qvis3/flow.c bsp/qvis3/qvis3.c

qdata3_SRCS = qdata/images.c qdata/models.c \
	qdata/qdata.c qdata/sprites.c \
	qdata/tables.c qdata/video.c
qbsp3_OBJS = $(qbsp3_SRCS:.c=.o)
qrad3_OBJS = $(qrad3_SRCS:.c=.o)
qvis3_OBJS = $(qvis3_SRCS:.c=.o)
qdata3_OBJS = $(qdata3_SRCS:.c=.o)

common_SRCS = common/bspfile.c common/cmdlib.c \
	common/l3dslib.c common/lbmlib.c \
	common/mathlib.c common/mdfour.c common/polylib.c \
	common/scriplib.c common/threads.c common/trilib.c

common_OBJS = $(common_SRCS:.c=.o)

CC=gcc
CFLAGS = -I./common -g -O2
LDFLAGS = -g
all: bspinfo3 qbsp3 qrad3 qvis3 qdata3

bspinfo3: $(bspinfo3_OBJS) libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(bspinfo3_OBJS) libcommon.a

qbsp3: $(qbsp3_OBJS) libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(qbsp3_OBJS) libcommon.a -lm

qrad3: $(qrad3_OBJS) libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(qrad3_OBJS) libcommon.a -lm

qvis3: $(qvis3_OBJS) libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(qvis3_OBJS) libcommon.a -lm

qdata3: $(qdata3_OBJS) libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(qdata3_OBJS) libcommon.a -lm

libcommon.a: $(common_OBJS)
	$(AR) rcs $@ $(common_OBJS)

clean:
	-rm -f $(qbsp3_OBJS) $(qrad3_OBJS) $(qvis3_OBJS) \
		$(common_OBJS) $(bspinfo3_OBJS)
	-rm -f bspinfo3 qbsp3 qrad3 qvis3 libcommon.a

.PHONY: all clean

