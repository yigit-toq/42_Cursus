# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2024/10/17 18:19:44 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	./sources/

INC_DIR			=	./includes/

LIB_DIR			=	./libraries/

SRCS			=	$(SRCS_DIR)cub3d.c	$(SRCS_DIR)errors.c

OBJS			=	$(SRCS:.c=.o)

RM				=	@rm -rf

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ./includes

LIBRARY			=	$(MLX) -framework OpenGL -framework AppKit

OS 				=	$(shell uname)

NAME			=	cub3d
BONUS			=	cub3d_bonus

LIBFT_DIR		=	$(LIB_DIR)libft/

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_MAKE		=	make -s -C $(LIBFT_DIR)
LIBFT_REPO		=	https://github.com/yigit-toq/42_Cursus.git

MLX_DIR			=	$(LIB_DIR)minilibx/

MLX_MAKE		=	make -s -C $(MLX_DIR) all > /dev/null 2>&1
MLX_LINUX		=	https://github.com/42Paris/minilibx-linux.git
MLX_MACOS		=	https://github.com/dannywillems/minilibx-mac-osx.git

COLOR_E			=	\033[0m
COLOR_R			=	\033[0;31m
COLOR_G			=	\033[0;32m
COLOR_Y			=	\033[0;33m
COLOR_B			=	\033[0;34m

ifeq ($(OS), Linux)
	MLX_REPO	=	$(MLX_LINUX)
	MLX			=	$(MLX_DIR)libmlx_Linux.a
else
	MLX_REPO	=	$(MLX_MACOS)
	MLX			=	$(MLX_DIR)libmlx.a
endif

all			:	$(NAME)

bonus		:	$(BONUS)

$(NAME)		:	$(MLX) $(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
				@printf "$(COLOR_B)CUB3D			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(BONUS)	:	$(MLX) $(LIBFT) $(BONUS_OBJS)
				$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJS) $(LIBFT) $(MLX)
				@printf "$(COLOR_B)CUB3D_BONUS		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

$(LIBFT)	:
				@if [ ! -d $(LIBFT_DIR) ]; then													\
					echo "libft directory not found...";										\
					git clone -b 0-libft $(LIBFT_REPO) $(LIBFT_DIR);							\
				fi; 																			\
				$(LIBFT_MAKE)	all

$(MLX)		:
				@if [ ! -d $(MLX_DIR) ]; then													\
					echo "mlx directory not found...";											\
					git clone $(MLX_REPO) $(MLX_DIR);											\
				fi; 																			\
				$(MLX_MAKE) 	all
				@printf "$(COLOR_B)MINILIBX		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

re			:	fclean all

clean		:
				$(RM) $(OBJS) $(BONUS_OBJS)
				@if [ -d $(MLX_DIR) ];		then $(MLX_MAKE)	clean;	fi
				@if [ -d $(LIBFT_DIR) ];	then $(LIBFT_MAKE)	clean;	fi
				@printf "$(COLOR_R)OBJECT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

fclean		:	clean
				$(RM) $(NAME) $(BONUS)
				@if [ -d $(LIBFT_DIR) ];	then $(LIBFT_MAKE)	fclean;	fi
				@printf "$(COLOR_R)EXECUT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

valgrind	:	all
				valgrind --leak-check=full ./$(NAME) test.cub

norminette	:
				@norminette $(INC_DIR) $(LIBFT_DIR) $(SRCS_DIR)

clean_repo	:	fclean
				$(RM) $(LIBFT_DIR) $(MLX_DIR)

.PHONY		:	all bonus re clean fclean valgrind norminette clean_repo