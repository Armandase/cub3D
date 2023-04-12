NAME		= cub3D
NAME_B		= cub3D_b
SRCS		= manda/srcs/main.c manda/srcs/utils_overall.c\
			  manda/srcs/parsing/parsing.c manda/srcs/parsing/extension.c\
			  manda/srcs/parsing/map_check.c manda/srcs/parsing/atoi_protect.c\
			  manda/srcs/parsing/texture_utils.c manda/srcs/parsing/get_map.c\
			  manda/srcs/parsing/verif_map.c\
			  manda/srcs/render/render.c manda/srcs/render/handlers.c\
			  manda/srcs/render/raycasting.c manda/srcs/render/drawing.c\
			  manda/srcs/render/utils.c manda/srcs/render/texture.c\
			  manda/srcs/render/init.c manda/srcs/render/utils_raycast.c\
			  manda/srcs/render/free.c

SRCS_B		= bonus/srcs/main.c bonus/srcs/utils_overall.c\
			  bonus/srcs/parsing/parsing.c bonus/srcs/parsing/extension.c\
			  bonus/srcs/parsing/map_check.c bonus/srcs/parsing/atoi_protect.c\
			  bonus/srcs/parsing/texture_utils.c bonus/srcs/parsing/get_map.c\
			  bonus/srcs/parsing/verif_map.c bonus/srcs/parsing/get_animation.c\
			  bonus/srcs/render/render.c bonus/srcs/render/handlers.c\
			  bonus/srcs/render/raycasting.c bonus/srcs/render/drawing.c\
			  bonus/srcs/render/utils.c bonus/srcs/render/texture.c\
			  bonus/srcs/render/minimap.c bonus/srcs/render/animation.c\
			  bonus/srcs/render/init.c bonus/srcs/render/utils_raycast.c\
			  bonus/srcs/render/free.c bonus/srcs/render/handler_door.c
CC			= clang
LIBMLX		= libs/MLX42
LIBS        = -Llibs/libft -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
CFLAGS		= -Wall -Werror -Wextra -g -Wno-conversion -Ofast
OBJS		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}

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
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=leak.supp ./${NAME} maps/map.cub 

re: fclean all

bonus: libmlx ${NAME_B}

libmlx:
	@cmake $(LIBMLX) -DDEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME_B): ${OBJS_B}
	@make -s -C ./libs/libft --no-print-directory
	${CC} ${CFLAGS} -o ${NAME_B} ${SRCS_B} ${LIBS}

clean_b:
	@rm -f ${OBJS_B}
	@rm -rf $(LIBMLX)/build
	make clean -Clibs/libft
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mBonus objects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean_b: clean_b
	@rm -f ${NAME_B}
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBonus binary removed\x1b[0m\e[5m 🚨\n\e[0m'

vg_b: bonus
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=leak.supp ./${NAME_B} maps/map.cub 

re_b: fclean_b bonus

.PHONY: all clean fclean re bonus clean_b fclean_b re_b
