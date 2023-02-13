NAME		= cub3d
SRCS		= main.c\
			  parsing/parsing.c parsing/extension.c\
			  parsing/map_check.c parsing/atoi_protect.c 
CC			= gcc
LIBS        = -Llibft -lft
CFLAGS		= -Wall -Werror -Wextra -g -gdwarf-4
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@make -s -C libft --no-print-directory
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

clean:
	@rm -f ${OBJS}
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mObjects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean : clean
	@rm -f ${NAME}
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBinary removed\x1b[0m\e[5m 🚨\n\e[0m'

re: fclean all

vg:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=.vsupp ./minishell

.PHONY: all clean fclean re vg
