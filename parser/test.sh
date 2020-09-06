#!/bin/bash

EXEC=./parser.out
LOG=valgrind.log

make test \
&& valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--show-reachable=yes \
	--log-file=$LOG \
	$EXEC < .test/test_subjects \
;

grep -A1 "valgrind" ${LOG}|grep $EXEC;
