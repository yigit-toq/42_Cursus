# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 23:48:56 by ytop              #+#    #+#              #
#    Updated: 2025/03/18 23:48:56 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ex02

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

FORM_DIR		=	$(SRCS_DIR)Form/

SRCS 			=	$(SRCS_DIR)main.cpp $(SRCS_DIR)Bureaucrat.cpp $(FORM_DIR)AForm.cpp $(FORM_DIR)ShrubberyCreationForm.cpp $(FORM_DIR)RobotomyRequestForm.cpp $(FORM_DIR)PresidentialPardonForm.cpp

OBJS 			=	$(SRCS:.cpp=.o)

RM				=	@rm -rf

CC				=	@c++
CFLAGS			=	-Wall -Wextra -Werror -I ./includes -I ./includes/Form

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
					@echo "\e[1m$(C_Y)EX00		$(C_G)[OK]\e[0m$(C_E)"

clean			:
					$(RM) -rf $(OBJS)
					@echo "\e[1m$(C_Y)OBJECTS		$(C_R)[KO]\e[0m$(C_E)"
			

fclean			:	clean
					@$(RM) $(NAME)
					@echo "\e[1m$(C_Y)EXECUTE		$(C_R)[KO]\e[0m$(C_E)"

re				:	fclean all

.PHONY			:	all clean fclean re
