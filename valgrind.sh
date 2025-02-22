#!/bin/bash

EXEC=./minishell
LOG=valgrind

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--track-origins=yes \
	--show-reachable=yes \
	--log-file=${LOG}.log \
	$EXEC $@ \
;

grep '==[0-9]*==' <valgrind.log --only-matching | sort --unique | tr -d = |
	while read -r pid; 
	do \
		pidlog=${LOG}.${pid}.log;
		echo $pidlog;
		grep "$pid" <${LOG}.log >$pidlog;
		grep -A1 "valgrind" $pidlog | grep $EXEC;
	done;
