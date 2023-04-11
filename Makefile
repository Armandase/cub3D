NAME		= cub3D
SRCS		= srcs/main.c srcs/utils_overall.c\
			  srcs/parsing/parsing.c srcs/parsing/extension.c\
			  srcs/parsing/map_check.c srcs/parsing/atoi_protect.c \
			  srcs/parsing/texture_utils.c srcs/parsing/get_map.c\
			  srcs/parsing/verif_map.c srcs/parsing/get_animation.c\
			  srcs/render/render.c srcs/render/handlers.c\
			  srcs/render/raycasting.c srcs/render/drawing.c\
			  srcs/render/utils.c srcs/render/texture.c\
			  srcs/render/minimap.c srcs/render/animation.c
CC			= clang
LIBMLX		= libs/MLX42
LIBS        = -Llibs/libft -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
CFLAGS		= -Wall -Werror -Wextra -g -Wno-conversion -Ofast
OBJS		= ${SRCS:.c=.o}

all: libmlx ${NAME}

libmlx:
	@cmake $(LIBMLX) -DDEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@make -s -C ./libs/libft --no-print-directory
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

clean:
	@rm -f ${OBJS}
	@rm -rf $(LIBMLX)/build
	make clean -Clibs/libft
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mObjects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean : clean
	@rm -f ${NAME}
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBinary removed\x1b[0m\e[5m 🚨\n\e[0m'

vg: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=leak.supp ./cub3D maps/map.cub 

re: fclean all

.PHONY: all clean fclean re
