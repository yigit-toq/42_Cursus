# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2024/12/24 20:00:11 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M_ERROR_DIR		=	$(M_SRCS_DIR)2-error/
B_ERROR_DIR		=	$(B_SRCS_DIR)2-error/

M_UTILS_DIR		=	$(M_SRCS_DIR)1-utils/
B_UTILS_DIR		=	$(B_SRCS_DIR)1-utils/

M_MAP_DIR		=	$(M_SRCS_DIR)0-map/
B_MAP_DIR		=	$(B_SRCS_DIR)0-map/

LIB_DIR			=	./libraries/
INC_DIR			=	./includes/

PROJECTS		=	./projects/

M_SRCS_DIR		=	$(PROJECTS)mandatory/
M_OBJS_DIR		=	objects_m/

B_SRCS_DIR		=	$(PROJECTS)bonus/
B_OBJS_DIR		=	objects_b/

M_SRCS			=	$(M_SRCS_DIR)cub3d.c $(M_SRCS_DIR)init.c $(M_SRCS_DIR)raycasting.c $(M_SRCS_DIR)input_system.c $(M_SRCS_DIR)minimap.c $(M_SRCS_DIR)rendering.c $(M_MAP_DIR)map.c $(M_MAP_DIR)map_utils.c $(M_UTILS_DIR)utils.c $(M_ERROR_DIR)error.c
B_SRCS			=	$(B_SRCS_DIR)cub3d.c $(B_SRCS_DIR)init.c $(B_SRCS_DIR)raycasting.c $(B_SRCS_DIR)input_system.c $(B_SRCS_DIR)minimap.c $(B_SRCS_DIR)rendering.c $(B_MAP_DIR)map.c $(B_MAP_DIR)map_utils.c $(B_UTILS_DIR)utils.c $(B_ERROR_DIR)error.c $(B_SRCS_DIR)animation.c $(B_SRCS_DIR)audio.c

M_OBJS			=	$(patsubst %.c, $(M_OBJS_DIR)/%.o, $(M_SRCS))
B_OBJS			=	$(patsubst %.c, $(B_OBJS_DIR)/%.o, $(B_SRCS))

RM				=	@rm -rf

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ./includes -g

OS 				=	$(shell uname)

NAME			=	cub3d
BONUS			=	cub3d_bonus

MLX_DIR			=	$(LIB_DIR)minilibx/

MLX_MAKE		=	make -s -C $(MLX_DIR) all > /dev/null 2>&1
MLX_LINUX		=	https://github.com/42Paris/minilibx-linux.git
MLX_MACOS		=	https://github.com/dannywillems/minilibx-mac-osx.git

LIBFT_DIR		=	$(LIB_DIR)libft/

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_MAKE		=	make -s -C $(LIBFT_DIR)
LIBFT_REPO		=	https://github.com/yigit-toq/42_Cursus.git

COLOR_E			=	\033[0m
COLOR_R			=	\033[0;31m
COLOR_G			=	\033[0;32m
COLOR_Y			=	\033[0;33m
COLOR_B			=	\033[0;34m

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

$(NAME)			:	$(MLX) $(LIBFT) $(M_OBJS)
					$(CC) $(CFLAGS) -o $(NAME)	$(M_OBJS) $(LIBFT) $(LIBRARY)
					@printf "$(COLOR_B)CUB3D			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(BONUS)		:	$(MLX) $(LIBFT) $(B_OBJS)
					$(CC) $(CFLAGS) -o $(BONUS)	$(B_OBJS) $(LIBFT) $(LIBRARY) -lSDL2
					@printf "$(COLOR_B)CUB3D_BONUS		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

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