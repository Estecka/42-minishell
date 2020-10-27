#!/bin/bash

EXEC=./minishell
LOG=valgrind.log

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--track-origins=yes \
	--show-reachable=yes \
	--log-file=$LOG \
	$EXEC $@ \
;

grep -A1 "valgrind" ${LOG}|grep $EXEC;
