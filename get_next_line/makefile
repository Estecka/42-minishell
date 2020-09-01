SRCS	= get_next_line.c \

OBJS	= ${SRCS:.c=.o}

HDRS	= \
	get_next_line.h \
	get_next_line_internals.h \

NAME	= libgnl.a

CC		= clang
CFLAGS	= -Wall -Wextra -Werror


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

${OBJS}: ${HDRS}

all: ${NAME}

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
