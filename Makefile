# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 17:07:12 by ytop              #+#    #+#              #
#    Updated: 2025/07/03 18:56:41 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv

SOURCES_DIR		=	./sources/
OBJECTS_DIR		=	./objects/

UTILS_DIR		=	${SOURCES_DIR}utils/

PROCESS_DIR		=	${SOURCES_DIR}process/
NETWORK_DIR		=	${SOURCES_DIR}network/

COMMAND_DIR		=	${SOURCES_DIR}command/

PROTOCOL_DIR	=	${SOURCES_DIR}protocol/

SRCS 			=	$(SOURCES_DIR)Main.cpp	$(PROCESS_DIR)Server.cpp	$(NETWORK_DIR)Socket.cpp			$(PROTOCOL_DIR)Message.cpp				$(UTILS_DIR)Utils.cpp		$(COMMAND_DIR)NickCommand.cpp	\
											$(PROCESS_DIR)Client.cpp	$(NETWORK_DIR)PollHandler.cpp		$(PROTOCOL_DIR)CommandHandler.cpp		$(UTILS_DIR)Logger.cpp		$(COMMAND_DIR)UserCommand.cpp	\
											$(PROCESS_DIR)Channel.cpp	$(NETWORK_DIR)SelectHandler.cpp		$(PROTOCOL_DIR)SpecificCommand.cpp																	\

OBJS 			=	$(SRCS:.cpp=.o)

RM				=	@rm -rf

CC				=	@c++

CFLAGS			=	-Wall  -Wextra -Werror	\
					-I ./includes/protocol	\
					-I ./includes/command	\
					-I ./includes/network	\
					-I ./includes/process	\
					-I ./includes/utils		\

STD				=	-std=c++98

C_Y				=	\033[0;33m
C_G				=	\033[0;32m
C_R				=	\033[0;31m
C_E				=	\033[0m

%.o				:	%.cpp
					@$(CC)	$(CFLAGS) $(STD) -c	$< -o $@

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC)	$(CFLAGS) $(STD)	$^ -o $(NAME)
					@echo "\e[1m$(C_Y)IRCSERV		$(C_G)[OK]\e[0m$(C_E)"

clean			:
					$(RM) -rf $(OBJS)
					@echo "\e[1m$(C_Y)OBJECTS		$(C_R)[KO]\e[0m$(C_E)"
			

fclean			:	clean
					@$(RM) $(NAME)
					@echo "\e[1m$(C_Y)EXECUTE		$(C_R)[KO]\e[0m$(C_E)"

re				:	fclean all

.PHONY			:	all clean fclean re
