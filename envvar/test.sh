#!/bin/bash

EXEC=./envvar.out
LOG=valgrind.log

make test \
&& valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--show-reachable=yes \
	--log-file=$LOG \
	$EXEC \
;

grep -A1 "valgrind" ${LOG}|grep $EXEC;
