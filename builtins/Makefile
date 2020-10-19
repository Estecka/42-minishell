HDRS	=	builtins.h \

SRCS	=	echo.c \
			pwd.c \
			env.c \
			cd.c \
			export.c \
			exit.c \
			execve.c \
			utils.c \
			unset.c \
			final_builtins.c

OBJS	= ${SRCS:.c=.o}


NAME	= lib_builtins.a

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address


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
