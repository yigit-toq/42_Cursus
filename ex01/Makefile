# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 23:48:56 by ytop              #+#    #+#              #
#    Updated: 2025/07/25 16:07:25 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ex01

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

SRCS 			=	$(SRCS_DIR)main.cpp $(SRCS_DIR)Bureaucrat.cpp $(SRCS_DIR)Form.cpp

OBJS 			=	$(SRCS:.cpp=.o)

RM				=	@rm -rf

CC				=	@c++
CFLAGS			=	-Wall -Wextra -Werror -I ./includes

STD				=	-std=c++98

C_Y				=	\033[0;33m
C_G				=	\033[0;32m
C_R				=	\033[0;31m
C_E				=	\033[0m

%.o				:	%.cpp
					@$(CC) $(CFLAGS) $(STD) -c $< -o $@

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $(STD) $^ -o $(NAME)
					@echo "\e[1m$(C_Y)EX01		$(C_G)[OK]\e[0m$(C_E)"

clean			:
					$(RM) $(OBJS)
					@echo "\e[1m$(C_Y)OBJECTS		$(C_R)[KO]\e[0m$(C_E)"
			

fclean			:	clean
					$(RM) $(NAME)
					@echo "\e[1m$(C_Y)EXECUTE		$(C_R)[KO]\e[0m$(C_E)"

re				:	fclean all

.PHONY			:	all clean fclean re
