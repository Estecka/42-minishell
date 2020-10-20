HDRS = \
	libft.h \
	libft_char.h \
	libft_malloc.h \
	libft_memory.h \
	libft_string.h \

SRCS	= \
	integer.c integer2.c \
	put_things.c put_things_fd.c \
	char/is_word.c \
	char/is_special.c \
	char/to_case.c \
	string/misc.c \
	string/strchr.c \
	string/strdup.c \
	string/strcmp.c \
	string/strlcpy.c \
	string/strstr.c \
	memory/meminit.c \
	memory/memcpy.c \
	memory/misc.c \
	malloc/free.c \
	malloc/malloc.c \

SRCS_BONUS = list.c list2.c

OBJS	= ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME	= libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus: ${OBJS} ${OBJS_BONUS}
	ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

${OBJS}: ${HDRS}
${OBJS_BONUS}: ${HDRS}

all: bonus

clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re bonus
