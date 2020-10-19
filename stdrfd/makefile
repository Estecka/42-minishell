HDRS	= stdrfd.h \

SRCS	= stdrfd.c \

OBJS	= ${SRCS:.c=.o}

TEST_LIBS = \
	../get_next_line/libgnl.a \

TEST_FLAGS = \
	-L ./ -lstdrfd \
	-L ../get_next_line -lgnl \

NAME	= libstdrfd.a
TEST	= test.out

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

test: ${TEST}
${TEST}: ${NAME} .test/main.c ${TEST_LIBS}
	gcc -o ${TEST} \
		.test/main.c \
		${TEST_FLAGS} \
		${CFLAGS} \

${OBJS}: ${HDRS}

all: ${NAME} ${TEST}

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re test
