GAME=testgame

all: 
	sh entities.sh
	install -d -m 755 gamepack
	install -d -m 766 gamepack/$(GAME).game
	install -d -m 766 gamepack/$(GAME).game/$(GAME)
	install -d -m 766 gamepack/games
	install -c -m 644 entities.def gamepack/$(GAME).game/$(GAME)
	install -c -m 644 $(GAME).game gamepack/games
	install -c -m 644 default_build_menu.xml game.xlink gamepack/$(GAME).game

clean:
	-rm -f entities.def
	-rm -Rf gamepack

.PHONY: all clean
