# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2025/01/16 19:10:41 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIB_DIR				=	./libraries/
INC_DIR				=	./includes/

PROJECTS			=	./projects/

M_SRCS_DIR			=	$(PROJECTS)mandatory/
M_OBJS_DIR			=	objects_m/

B_SRCS_DIR			=	$(PROJECTS)bonus/
B_OBJS_DIR			=	objects_b/

M_SRCS				=	$(M_SRCS_DIR)so_long.c																							\
						\
						$(M_SRCS_DIR)0-graphic/graphics.c																				\
						\
						$(M_SRCS_DIR)1-control/controls.c					$(M_SRCS_DIR)1-control/error.c								\
						\
						$(M_SRCS_DIR)2-map/map.c							$(M_SRCS_DIR)2-map/map_utils.c								\


B_SRCS				=	$(B_SRCS_DIR)so_long.c																							\
						\
						$(B_SRCS_DIR)0-animation/animations_player.c		$(B_SRCS_DIR)0-animation/animations_object.c				\
						\
						$(B_SRCS_DIR)1-graphic/graphics.c					$(B_SRCS_DIR)1-graphic/add_image.c							\
						\
						$(B_SRCS_DIR)2-control/controls.c					$(B_SRCS_DIR)2-control/error_ctr.c							\
						\
						$(B_SRCS_DIR)3-enemy/enemy.c						$(B_SRCS_DIR)3-enemy/enemy_utils.c							\
						\
						$(B_SRCS_DIR)4-map/map.c							$(B_SRCS_DIR)4-map/map_utils.c								\

M_OBJS				=	$(patsubst %.c, $(M_OBJS_DIR)/%.o, $(M_SRCS))
B_OBJS				=	$(patsubst %.c, $(B_OBJS_DIR)/%.o, $(B_SRCS))

RM					=	@rm -rf

CC					=	@cc
CFLAGS				=	-Wall -Wextra -Werror -I ./includes -I ./includes/utils -I $(MLX_DIR) -g

OS 					=	$(shell uname)

NAME				=	so_long
BONUS				=	so_long_bonus

MLX_DIR				=	$(LIB_DIR)minilibx/

MLX_MAKE			=	make -s -C $(MLX_DIR) all > /dev/null 2>&1
MLX_LINUX			=	https://github.com/42Paris/minilibx-linux.git
MLX_MACOS			=	https://github.com/dannywillems/minilibx-mac-osx.git

LIBFT_DIR			=	$(LIB_DIR)libft/

LIBFT				=	$(LIBFT_DIR)libft.a
LIBFT_MAKE			=	make -s -C $(LIBFT_DIR)
LIBFT_REPO			=	https://github.com/yigit-toq/42_Cursus.git

COLOR_E				=	\033[0m
COLOR_R				=	\033[0;31m
COLOR_G				=	\033[0;32m
COLOR_Y				=	\033[0;33m
COLOR_B				=	\033[0;34m

ifeq ($(OS), Linux)
	MLX_REPO	=	$(MLX_LINUX)

	MLX			=	$(MLX_DIR)libmlx_Linux.a

	LIBRARY		=	$(MLX) -lXext -lX11 -lm -lz
else
	MLX_REPO	=	$(MLX_MACOS)

	MLX			=	$(MLX_DIR)libmlx.a

	LIBRARY		=	$(MLX) -framework OpenGL AppKit
endif

$(M_OBJS_DIR)/%.o	: 	%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJS_DIR)/%.o	: 	%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

all				:	$(NAME)

bonus			:	$(BONUS)

$(NAME)			:	$(MLX)	$(LIBFT) $(M_OBJS)
					$(CC)	$(CFLAGS) -o $(NAME) $(M_OBJS) $(LIBFT) $(LIBRARY)

					@printf "$(COLOR_B)SO_LONG			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(BONUS)		:	$(MLX)	$(LIBFT) $(B_OBJS)
					$(CC)	$(CFLAGS) -o $(BONUS) $(B_OBJS) $(LIBFT) $(LIBRARY)
					@printf "$(COLOR_R)\n"	
					@echo "  ██████  ▒█████   ██▓     ▒█████   ███▄   ██   ▄████ "; sleep 0.1
					@echo "▒██    ▒ ▒██▒  ██▒▓██▒    ▒██▒  ██▒ ██ ▀█  ██  ██▒ ▀█▒"; sleep 0.1
					@echo "░ ▓██▄   ▒██░  ██▒▒██░    ▒██░  ██▒▓██  ▀█ ██▒▒██░▄▄▄░";	sleep 0.1
					@echo "  ▒   ██▒▒██   ██░▒██░    ▒██   ██░▓██▒  ▐▌██▒░▓█  ██▓";	sleep 0.1
					@echo "▒██████▒▒░ ████▓▒░░██████▒░ ████▓▒░▒██░   ▓██░░▒▓███▀▒";	sleep 0.1
					@echo "▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ░ ▒░▓  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒  ░▒   ▒ ";	sleep 0.1
					@echo "░ ░▒  ░ ░  ░ ▒ ▒░ ░ ░ ▒  ░  ░ ▒ ▒░ ░ ░░   ░ ▒░  ░   ░ ";	sleep 0.1
					@echo "░  ░  ░  ░ ░ ░ ▒    ░ ░   ░ ░ ░ ▒     ░   ░ ░ ░ ░   ░ ";	sleep 0.1
					@echo "      ░      ░ ░      ░  ░    ░ ░           ░       ░ ";	sleep 0.1
					@printf "$(COLOR_E)\n"

$(LIBFT)		:
					@if [ ! -d $(LIBFT_DIR) ]; then													\
						echo "libft directory not found...";										\
						git clone -b 00-libft $(LIBFT_REPO) $(LIBFT_DIR);							\
					fi; 																			\
					$(LIBFT_MAKE)	all

$(MLX)			:
					@if [ ! -d $(MLX_DIR) ]; then													\
						echo "mlx directory not found...";											\
						git clone $(MLX_REPO) $(MLX_DIR);											\
					fi; 																			\
					$(MLX_MAKE) 	all
					@printf "$(COLOR_B)MINILIBX		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

re				:	fclean all

clean			:
					$(RM) $(M_OBJS_DIR) $(B_OBJS_DIR)
					@if [ -d $(LIBFT_DIR) ];		then $(LIBFT_MAKE)	clean;	fi
					@if [ -d $(MLX_DIR)   ];		then $(MLX_MAKE)	clean;	fi
					@printf "$(COLOR_R)OBJECT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

fclean			:	clean
					$(RM) $(NAME) $(BONUS)
					@if [ -d $(LIBFT_DIR) ];	then $(LIBFT_MAKE)	fclean;	fi
					@printf "$(COLOR_R)EXECUT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

valgrind		:	all
					valgrind --leak-check=full ./$(NAME) test.cub

norminette		:
					@norminette $(INC_DIR) $(LIBFT_DIR) $(M_SRCS_DIR) $(B_SRCS_DIR)

clean-repo		:	fclean
					$(RM) $(LIBFT_DIR) $(MLX_DIR)

.PHONY			:	all bonus re clean fclean valgrind norminette clean_repo
