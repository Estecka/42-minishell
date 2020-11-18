HDRS = \
	parser.h \
	parser_internals.h \

SRCS = \
	parser.c \
	procexpr.c \
	exprbuilder.c \
	exprbuilder_abort.c \
	argument.c \
	quotes.c \
	punctuation.c \
	variables.c \
	multivar.c \

OBJS = ${SRCS:.c=.o}

TEST_SRCS = \
	.test/main.c \

TEST_OBJS = ${TEST_SRCS:.c=.o}

NAME = libparser.a
TEST = parser.out

LIBS = \
	../libft/libft.a \
	../get_next_line/libgnl.a \
	../dynarray/libdynarray.a \

CC     = clang
CFLAGS = -Wall -Wextra -Werror
TESTFLAGS = \
	-Wall -Wextra \
	-L ./ -lparser \
	-L ../libft/ -lft \
	-L ../get_next_line/ -lgnl \
	-L ../dynarray/ -ldynarray \


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

test: ${TEST} ${TEST_OBJS}
${TEST}: ${NAME} ${TEST_OBJS} ${LIBS}
	${CC} ${TEST_OBJS} -o ${TEST} \
		${TESTFLAGS}


${OBJS}: ${HDRS}

%.a: ext_makefile
	make $(@F) -C $(@D)


all: ${NAME} test

clean:
	rm -f *.o
	rm -f *.gch

fclean:
	rm -f *.o
	rm -f *.gch
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	all clean fclean re \
	ext_makefile \
	test \
