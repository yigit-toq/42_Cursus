# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 15:13:54 by ytop              #+#    #+#              #
#    Updated: 2024/08/16 17:10:15 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	./sources/

BONUS_DIR	=	./sources_bonus/

SRCS		=	$(SRCS_DIR)so_long.c								$(SRCS_DIR)controls.c								$(SRCS_DIR)errors.c			\
				$(SRCS_DIR)map/map.c								$(SRCS_DIR)map/map_utils.c														\
				$(SRCS_DIR)graphic/graphics.c																										\

BONUS_SRCS	=	$(BONUS_DIR)so_long_bonus.c																											\
				$(BONUS_DIR)0-animation/animations_player_bonus.c	$(BONUS_DIR)0-animation/animations_object_bonus.c								\
				$(BONUS_DIR)1-graphic/graphics_bonus.c				$(BONUS_DIR)1-graphic/add_image_bonus.c											\
				$(BONUS_DIR)2-control/controls_bonus.c				$(BONUS_DIR)2-control/error_ctr_bonus.c											\
				$(BONUS_DIR)3-enemy/enemy_bonus.c					$(BONUS_DIR)3-enemy/enemy_utils_bonus.c											\
				$(BONUS_DIR)4-map/map_bonus.c						$(BONUS_DIR)4-map/map_utils_bonus.c												\

OBJS		=	$(SRCS:.c=.o)

BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

CC			=	@cc
CFLAGS		=	-Wall -Wextra -Werror -I ./includes

RM			=	@rm -rf

NAME		=	so_long
BONUS		=	so_long_bonus

MLX_MAKE	=	@make -C ./minilibx
MLX			=	./minilibx/libmlx.a

LIBFT_MAKE	=	@make -C ./libft
LIBFT		=	./libft/libft.a

LIBRARY		=	./minilibx/libmlx.a -framework OpenGL -framework AppKit

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all			:	$(NAME)

bonus		:	$(BONUS)

$(NAME)		:	$(MLX) $(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBRARY)
				@printf "SO_LONG		$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END) \n"

$(BONUS)	:	$(MLX) $(LIBFT) $(BONUS_OBJS)
				$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJS) $(LIBFT) $(LIBRARY)
				@printf "$(COLOR_RED)\n"	
				@echo "  ██████  ▒█████   ██▓     ▒█████   ███▄   ██   ▄████ "; sleep 0.1
				@echo "▒██    ▒ ▒██▒  ██▒▓██▒    ▒██▒  ██▒ ██ ▀█  ██  ██▒ ▀█▒"; sleep 0.1
				@echo "░ ▓██▄   ▒██░  ██▒▒██░    ▒██░  ██▒▓██  ▀█ ██▒▒██░▄▄▄░";	sleep 0.1
				@echo "  ▒   ██▒▒██   ██░▒██░    ▒██   ██░▓██▒  ▐▌██▒░▓█  ██▓";	sleep 0.1
				@echo "▒██████▒▒░ ████▓▒░░██████▒░ ████▓▒░▒██░   ▓██░░▒▓███▀▒";	sleep 0.1
				@echo "▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ░ ▒░▓  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒  ░▒   ▒ ";	sleep 0.1
				@echo "░ ░▒  ░ ░  ░ ▒ ▒░ ░ ░ ▒  ░  ░ ▒ ▒░ ░ ░░   ░ ▒░  ░   ░ ";	sleep 0.1
				@echo "░  ░  ░  ░ ░ ░ ▒    ░ ░   ░ ░ ░ ▒     ░   ░ ░ ░ ░   ░ ";	sleep 0.1
				@echo "      ░      ░ ░      ░  ░    ░ ░           ░       ░ ";	sleep 0.1
				@printf "$(COLOR_END)\n"
				@printf "SO_LONG_BONUS	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

clean		:
				$(RM) $(OBJS) $(BONUS_OBJS)
				$(MLX_MAKE) clean
				$(LIBFT_MAKE) clean
				@printf "OBJECT FILES		$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

fclean		:	clean
				$(RM) $(NAME) $(BONUS)
				$(LIBFT_MAKE) fclean
				@printf "EXECUTABLE FILES	$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

re			:	fclean all

$(LIBFT)	:	
				$(LIBFT_MAKE) all

$(MLX)		:
				$(MLX_MAKE) all
				@printf "MINILIBX	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

.PHONY		:	all clean fclean re bonus
