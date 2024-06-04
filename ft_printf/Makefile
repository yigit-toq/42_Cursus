# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 03:14:51 by ytop              #+#    #+#              #
#    Updated: 2023/12/30 03:14:51 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= ./sources/ft_printf.c ./sources/ft_printf_utils.c ./sources/ft_utils.c
OBJ		= $(SRC:.c=.o)

CC		= @cc
CFLAGS	= -Wall -Wextra -Werror

RM		= @rm -rf

NAME	= libftprintf.a

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			@ar rcs $(NAME) $(OBJ)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re