#!/bin/zsh

DIRS=(
	.
	builtin
	dynarray
	envvar
	get_next_line
	libft
	parser
	stdrfd
	);

for d in $DIRS;
do;
	~/.norminette/norminette.rb \
		${d}/*.c \
		${d}/*.h \
		;
done;