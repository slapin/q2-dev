# from quake2 makefile
ARCH=$(uname -m | sed -e s/i.86/i386/ -e s/sun4u/sparc/ -e s/sparc64/sparc/ -e s/arm.*/arm/ -e s/sa110/arm/ -e s/alpha/axp/)
install -m 755 -d ./deploy
install -m 755 -d ./deploy/testgame
install -c -m 644 ./game/debug${ARCH}/game${ARCH}.so ./deploy/testgame
install -c -m 755 ./quake2/debug${ARCH}/quake2 ./deploy
install -c -m 755 ./quake2/debug${ARCH}/ref_softsdl.so ./deploy
install -c -m 644 ./testmaps/default.cfg ./deploy/testgame
install -m 755 -d ./deploy/testgame/maps
install -m 755 -d ./deploy/testgame/textures
install -m 755 -d ./deploy/testgame/pics
install -m 755 -d ./deploy/testgame/env
cp -a ./testmaps/maps/*.bsp ./deploy/testgame/maps/
cp -a ./testmaps/textures/* ./deploy/testgame/textures/
cp -a ./testmaps/pics/* ./deploy/testgame/pics/
cp -a ./testmaps/env/* ./deploy/testgame/env/
rm -Rf ./deploy/radiant
cp -a ./netradiant3/install ./deploy/radiant
install -d -m 755 ./deploy/radiant/games
cp -a ./game/scripts/gamepack/games/*.game ./deploy/radiant/games
cp -a ./game/scripts/gamepack/*.game ./deploy/radiant

