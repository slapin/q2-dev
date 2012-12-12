#!/bin/sh

for src in ../src/game/*.c;do
	awk -f entities.awk < $src
done > entities.def

