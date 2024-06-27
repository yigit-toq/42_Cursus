# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 20:10:24 by ytop              #+#    #+#              #
#    Updated: 2024/06/27 16:23:28 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR				=	./sources/

SRCS			=	$(DIR)philo.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror

RM				=	@rm -rf

NAME			=	philo

COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
					@printf "PHILOSOPHERS	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

clean			:
					$(RM) $(OBJS)
					@printf "PHILOSOPHERS	$(COLOR_RED)\e[1m[OK]\e[0m\n$(COLOR_END)"

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
