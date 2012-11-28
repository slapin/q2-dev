#!/bin/sh

set -e
(cd quake2 && make)
(cd game && make)
(cd gtkradiant && scons)
(cd netradiant && make)

