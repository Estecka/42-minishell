HDRS = \
	minishell.h \

SRCS = \
	main.c \
	exec_cmd.c \
	bootstrap_fd.c \

OBJS = ${SRCS:.c=.o}

LIBS = \
	libft/libft.a \
	dynarray/libdynarray.a \
	get_next_line/libgnl.a \
	envvar/libenvvar.a \
	parser/libparser.a \
	envvar/libenvvar.a \
	builtin/lib_builtins.a \
	stdrfd/libstdrfd.a \

NAME	= minishell

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L builtin -l_builtins \
	-L parser -lparser \
	-L envvar -lenvvar \
	-L stdrfd -lstdrfd \
	-L libft -lft \
	-L dynarray -ldynarray \
	-L get_next_line -lgnl \

${NAME}: ${LIBS} ${OBJS} 
	${CC} ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \


%.a: sub_makefile
	make $(@F) -C $(@D)

${OBJS}: ${HDRS}


all: ${NAME}

clean:
	for lib in ${LIBS}; do \
		make clean -C $$(dirname $$lib) ;\
	done
	rm -f *.o
	rm -f *.gch

fclean:
	for lib in ${LIBS}; do \
		make fclean -C $$(dirname $$lib) ;\
	done
	rm -f *.o
	rm -f *.gch
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	sub_makefile \
	all clean fclean re \
	test \
