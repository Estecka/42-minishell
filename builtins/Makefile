SRCS	= echo.c \

OBJS	= ${SRCS:.c=.o}


NAME	= lib_builtins.a

CC		= clang
CFLAGS	= -Wall -Wextra -Werror


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

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
