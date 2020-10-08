SRCS	= main.c \

OBJS	= ${SRCS:.c=.o}

LIBS = \
	libft/libft.a \
	dynarray/libdynarray.a \
	get_next_line/libgnl.a \
	envvar/libenvvar.a \
	parser/libparser.a \
	builtins/lib_builtins.a

NAME	= minishell

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L libft -lft \
	-L dynarray -ldynarray \
	-L get_next_line -lgnl \
	-L parser -lparser \
	-L builtins -l_builtins \
	-L envvar -lenvvar

TEST = .test_hh/test.out

TEST_SRCS = \
	main.c \

TEST_OBJS = ${TEST_SRCS:.c=.o}


${NAME}: ${LIBS} ${OBJS}
	clang ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

test: ${TEST} ${TEST_OBJS}
${TEST}: ${NAME} ${TEST_OBJS} ${LIBS}
	${CC} ${TEST_OBJS} -o ${TEST} \
		${LIBFLAGS}

%.a: sub_makefile
	make $(@F) -C $(@D)



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
	minilibx \
