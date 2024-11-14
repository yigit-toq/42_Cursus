# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2024/11/14 15:31:56 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ERROR_DIR		=	$(SRCS_DIR)2-error/
UTILS_DIR		=	$(SRCS_DIR)1-utils/
MAP_DIR			=	$(SRCS_DIR)0-map/

LIB_DIR			=	./libraries/
INC_DIR			=	./includes/

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

SRCS			=	$(SRCS_DIR)cub3d.c $(SRCS_DIR)init.c $(SRCS_DIR)input_system.c $(SRCS_DIR)minimap.c $(SRCS_DIR)rendering.c $(MAP_DIR)map.c $(MAP_DIR)map_utils.c $(UTILS_DIR)utils.c $(ERROR_DIR)error.c

M_OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

RM				=	@rm -rf

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ./includes

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

	LIBRARY		=	$(MLX) -lXext -lX11 -lm

	CFLAGS		+=	-DW=119			\
					-DA=97			\
					-DS=115			\
					-DD=100			\
					-DM=109			\
					-DLEFT=65361	\
					-DRIGHT=65363	\
					-DUP=65362		\
					-DDOWN=65364	\
					-DESC=65307		\
					-DSPACE=32		\
					-DLEFT=65361	\
					-DRIGHT=65363
else
	MLX_REPO	=	$(MLX_MACOS)

	MLX			=	$(MLX_DIR)libmlx.a

	LIBRARY		=	$(MLX) -framework OpenGL -framework AppKit

	CFLAGS		+=	-DW=13			\
					-DA=0			\
					-DS=1			\
					-DD=2			\
					-DM=46			\
					-DLEFT=123		\
					-DRIGHT=124		\
					-DUP=126		\
					-DDOWN=125		\
					-DESC=53		\
					-DSPACE=49		\
					-DLEFT=123		\
					-DRIGHT=124
endif

$(OBJS_DIR)/%.o	: 	%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

all				:	$(NAME)

bonus			:	$(BONUS)

$(NAME)			:	$(MLX) $(LIBFT) $(M_OBJS)
					$(CC) $(CFLAGS) -o $(NAME)	$(M_OBJS) $(LIBFT) $(LIBRARY)
					@printf "$(COLOR_B)CUB3D			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(BONUS)		:	$(MLX) $(LIBFT) $(B_OBJS)
					$(CC) $(CFLAGS) -o $(BONUS)	$(B_OBJS) $(LIBFT) $(LIBRARY)
					@printf "$(COLOR_B)CUB3D_BONUS		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(LIBFT)		:
					@if [ ! -d $(LIBFT_DIR) ]; then													\
						echo "libft directory not found...";										\
						git clone -b 0-libft $(LIBFT_REPO) $(LIBFT_DIR);							\
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
					$(RM) $(OBJS_DIR)
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
					@norminette $(INC_DIR) $(LIBFT_DIR) $(SRCS_DIR)

clean-repo		:	fclean
					$(RM) $(LIBFT_DIR) $(MLX_DIR)

.PHONY			:	all bonus re clean fclean valgrind norminette clean_repo