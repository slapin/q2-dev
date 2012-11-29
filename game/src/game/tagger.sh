#!/bin/sh
ctags -x --c-kinds=v --file-scope=no *.[ch] >../README.globals

for s in `cat ../README.globals|awk '{print $1}'`; do
	echo $s usage ===
	grep -wnH $s *.c
done >../README.globals_usage

