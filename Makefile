# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 17:02:40 by ytop              #+#    #+#              #
#    Updated: 2024/09/26 18:13:19 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

SRCS			=	$(SRCS_DIR)minishell.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ./includes

RM				=	@rm -rf

NAME			=	minishell

LIBFT_MAKE		=	@make -C ./libft
LIBFT			=	./libft/libft.a

RDFLAGS			=	-lreadline

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RDFLAGS)
					@printf "MINISHELL		$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END) \n"

clean			:
					$(RM) $(OBJS)
					$(LIBFT_MAKE) clean
					@printf "OBJECT FILES		$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

fclean			:	clean
					$(RM) $(NAME)
					$(LIBFT_MAKE) fclean
					@printf "EXECUTABLE FILES	$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

re				:	fclean all

$(LIBFT)		:	
					$(LIBFT_MAKE) all

.PHONY			:	all clean fclean re