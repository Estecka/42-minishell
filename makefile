SRCS	= main.c \

OBJS	= ${SRCS:.c=.o}

LIBS = \
	libft/libft.a \


NAME	= minishell

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L libft -lft \



${NAME}: ${LIBS} ${OBJS}
	clang ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

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
