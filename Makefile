# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:04:41 by ytop              #+#    #+#              #
#    Updated: 2024/10/16 18:16:50 by ytop             ###   ########.fr        #
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

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all			:	$(NAME)

bonus		:	$(BONUS)

$(NAME)		:	$(MLX) $(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(LIBRARY) -o $(NAME)	$(LIBFT) $(OBJS)
				@printf "CUB3D			$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)\n"

$(BONUS)	:	$(MLX) $(LIBFT) $(BONUS_OBJS)
				$(CC) $(CFLAGS) $(LIBRARY) -o $(BONUS)	$(LIBFT) $(BONUS_OBJS)
				@printf "CUB3D_BONUS	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)\n"

$(LIBFT)	:	
				$(LIBFT_MAKE)	all

$(MLX)		:
				$(MLX_MAKE) 	all
				@printf "MINILIBX		$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

re			:	fclean all

clean		:
				$(RM) $(OBJS)	$(BONUS_OBJS)
				$(LIBFT_MAKE)	clean
				$(MLX_MAKE)		clean
				@printf "OBJECT FILES		$(COLOR_RED)\e[1m[KO]\e[0m\n$(COLOR_END)"

fclean		:	clean
				$(RM) $(NAME) $(BONUS)
				$(LIBFT_MAKE) fclean
				@printf "EXECUT FILES		$(COLOR_RED)\e[1m[KO]\e[0m\n$(COLOR_END)"

.PHONY		:	all bonus re clean fclean