# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 19:12:29 by ytop              #+#    #+#              #
#    Updated: 2025/07/28 21:01:22 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	whatever

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

SRCS 			=	$(SRCS_DIR)main.cpp

OBJS 			=	$(SRCS:.cpp=.o)

RM				=	@rm -rf

CXX				=	@c++
CXXFLAGS		=	-Wall -Wextra -Werror -I ./includes

STD				=	-std=c++98

C_Y				=	\033[0;33m
C_G				=	\033[0;32m
C_R				=	\033[0;31m
C_E				=	\033[0m

%.o				:	%.cpp
					$(CXX) $(CXXFLAGS) $(STD) -c $< -o $@

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CXX) $(CXXFLAGS) $(STD) $^ -o $(NAME)
					@echo "\e[1m$(C_Y)EX00		$(C_G)[OK]\e[0m$(C_E)"

clean			:
					$(RM) $(OBJS)
					@echo "\e[1m$(C_Y)OBJECTS		$(C_R)[KO]\e[0m$(C_E)"
			

fclean			:	clean
					$(RM) $(NAME)
					@echo "\e[1m$(C_Y)EXECUTE		$(C_R)[KO]\e[0m$(C_E)"

re				:	fclean all

.PHONY			:	all clean fclean re
