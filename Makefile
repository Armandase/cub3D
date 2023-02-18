NAME		= cub3D
SRCS		= srcs/main.c srcs/utils_overall.c\
			  srcs/parsing/parsing.c srcs/parsing/extension.c\
			  srcs/parsing/map_check.c srcs/parsing/atoi_protect.c \
			  srcs/parsing/texture_utils.c srcs/parsing/get_map.c\
			  srcs/parsing/verif_map.c\
			  srcs/render/render.c srcs/render/handlers.c\
			  srcs/render/raycasting.c srcs/render/drawing.c
CC			= clang
LIBS        = -Llibs/libft -lft
MLX = -Llibs/mlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS		= -Wall -Werror -Wextra -g
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@make -s -C ./libs/libft --no-print-directory
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS} ${MLX}

clean:
	@rm -f ${OBJS}
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mObjects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean : clean
	@rm -f ${NAME}
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBinary removed\x1b[0m\e[5m 🚨\n\e[0m'

re: fclean all

.PHONY: all clean fclean re
