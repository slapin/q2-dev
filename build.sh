#!/bin/sh

set -e
(cd quake2 && make)
(cd game && make)
(cd gtkradiant && scons)
#(cd netradiant && make)
#(cd netradiant2 && make)
#(cd netradiant3 && make)

