QBSP = ../q2tools/qbsp3
QVIS = ../q2tools/qvis3
QRAD = ../q2tools/qrad3
QDATA = ../q2tools/qdata3

PICS_pics = num_0.pcx num_1.pcx i_health.pcx w_blaster.pcx \
	m_main_multiplayer.pcx m_main_options.pcx pause.pcx \
	m_main_video.pcx m_main_quit.pcx m_main_plaque.pcx \
	m_main_logo.pcx m_main_game_sel.pcx m_banner_game.pcx \
	m_cursor0.pcx m_cursor1.pcx m_cursor2.pcx m_cursor3.pcx \
	m_cursor4.pcx m_cursor5.pcx m_cursor6.pcx m_cursor7.pcx \
	m_cursor8.pcx m_cursor9.pcx m_cursor10.pcx m_cursor11.pcx \
	m_cursor12.pcx m_cursor13.pcx m_cursor14.pcx \
	i_help.pcx help.pcx conback.pcx
PICS_misc = 005.pcx 009.pcx IxirGround.pcx NewGravel.pcx WaterF.pcx
PICS_common = caulk.pcx

PICS = $(patsubst %,textures/misc/%,$(PICS_misc))
PICS += $(patsubst %,textures/common/%,$(PICS_common))
WALS = $(PICS:.pcx=.wal)

GENERATED_PICS = $(patsubst %,pics/%,$(PICS_pics))
MAPS = maps/testmap.map maps/wicked.map maps/house.map
BSPS = $(MAPS:.map=.bsp)

all: $(BSPS) $(GENERATED_PICS)

$(WALS): $(PICS) pics/palette.pcx
	$(QDATA) -obj -gamedir $(CURDIR) omg.qgr

pics/palette.pcx:
	convert textures/*/*.pcx textures/*/*.tga +append -colors 256 -unique-colors $@

%.pcx: %.tga
	convert $*.tga -colors 250 $*.pcx

%.bsp: %.map
	$(QBSP) $<
	$(QVIS) $*
	$(QRAD) -gamedir $(CURDIR) -threads 6 -ambient 0.2 -scale 1.0 -direct 0.01 -entity 1.3 -maxlight 1.2 $*
clean:
	-rm -f textures/misc/*.pcx
	-rm -f textures/common/*.pcx
	-rm -f maps/testmap.prt maps/testmap.bsp
	-rm -f pics/colormap.pcx
	-rm -f $(GENERATED_PICS)
	-rm -f $(BSPS)

.PHONY: all

maps/testmap.bsp: maps/testmap.map $(WALS)
maps/wicked.bsp: maps/wicked.map $(WALS)

maps/house.bsp: maps/house.map $(WALS)
	$(QBSP) $<
	$(QVIS) maps/house
	$(QRAD) -gamedir $(CURDIR) -chop 128 -threads 6 -ambient 0.1 -scale 1.0 -direct 0.01 -entity 1.0 maps/house


$(GENERATED_PICS): placeholder.pcx
	for g in $(GENERATED_PICS); do cp placeholder.pcx $$g;done

