HDRS = \
	envvar.h \

SRCS = \
	envvar.c \
	envvar2.c \
	envclear.c \
	shlvl.c \
	varnames.c \

OBJS = ${SRCS:.c=.o}

TEST_SRCS = \
	.test/main.c \

TEST_OBJS = ${TEST_SRCS:.c=.o}

NAME = libenvvar.a
TEST = envvar.out

LIBS = \
	../libft/libft.a \
	../dynarray/libdynarray.a \

CC     = clang
CFLAGS = -Wall -Wextra -Werror
TESTFLAGS = \
	-Wall -Wextra \
	-L ./ -lenvvar \
	-L ../libft/ -lft \
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
