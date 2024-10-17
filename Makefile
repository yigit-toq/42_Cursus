# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2024/10/17 17:42:39 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	./sources/

SRCS			=	$(SRCS_DIR)cub3d.c $(SRCS_DIR)errors.c

OBJS			=	$(SRCS:.c=.o)

RM				=	@rm -rf

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ./includes

LIB_DIR			=	./libraries/

LIBRARY			=	$(LIB_DIR)minilibx/libmlx.a -framework OpenGL -framework AppKit

NAME			=	cub3d
BONUS			=	cub3d_bonus

LIBFT			=	$(LIB_DIR)libft/libft.a
LIBFT_MAKE		=	@make -C $(LIB_DIR)libft

MLX				=	$(LIB_DIR)minilibx/libmlx.a
MLX_MAKE		=	@make -C $(LIB_DIR)minilibx

COLOR_E			=	\033[0m
COLOR_R			=	\033[0;31m
COLOR_G			=	\033[0;32m
COLOR_Y			=	\033[0;33m
COLOR_B			=	\033[0;34m

OS 				=	$(shell uname)

ifeq ($(OS), Linux)
    OS_TYPE = Linux
endif

all			:	$(NAME)

bonus		:	$(BONUS)

$(NAME)		:	$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME)	$(LIBFT) $(OBJS)
				@printf "$(COLOR_B)CUB3D			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)\n"

$(BONUS)	:	$(LIBFT) $(BONUS_OBJS)
				$(CC) $(CFLAGS) -o $(BONUS)	$(LIBFT) $(BONUS_OBJS)
				@printf "$(COLOR_B)CUB3D_BONUS		$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)\n"

$(LIBFT)	:
				$(LIBFT_MAKE)	all

$(MLX)		:
				$(MLX_MAKE) 	all
				@printf "$(COLOR_B)MINILIBX			$(COLOR_G)\e[1m[ OK ]\e[0m\n$(COLOR_E)"

re			:	fclean all

clean		:
				$(RM) $(OBJS)	$(BONUS_OBJS)
				$(LIBFT_MAKE)	clean
				@printf "$(COLOR_R)OBJECT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

fclean		:	clean
				$(RM) $(NAME) $(BONUS)
				$(LIBFT_MAKE) fclean
				@printf "$(COLOR_R)EXECUT FILES		\e[1m[ RM ]\e[0m\n$(COLOR_E)"

.PHONY		:	all bonus re clean fclean