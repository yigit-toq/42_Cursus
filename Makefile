# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 17:29:20 by ytop              #+#    #+#              #
#    Updated: 2024/05/29 21:01:13 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR				=	./sources/

SRCS			=	$(DIR)push_swap.c $(DIR)push_swap_utils.c $(DIR)action.c $(DIR)radix_sort.c $(DIR)selection_sort.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror

RM				=	@rm -rf

LIBFT			=	./libft/libft.a
LIBFT_MAKE		=	@make -C ./libft

NAME			=	push_swap

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
					@printf "PUSH_SWAP	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

$(LIBFT)		:
					$(LIBFT_MAKE) all

clean			:
					$(RM) $(OBJS)
					$(LIBFT_MAKE) clean
					@printf "PUSH_SWAP	$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

fclean			:	clean
					$(RM) $(NAME)
					$(RM) $(LIBFT)

re				:	fclean all

.PHONY			:	all clean fclean re
