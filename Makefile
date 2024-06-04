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

SRC		= ft_printf.c ft_printf_utils.c
OBJ		= $(SRC:.c=.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

NAME	= libftprintf.a

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY	: all clean fclean re