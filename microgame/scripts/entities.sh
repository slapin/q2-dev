#!/bin/sh

for src in ../src/*.c;do
	awk -f entities.awk < $src
done > entities.def

