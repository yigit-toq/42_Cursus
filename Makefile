# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 13:31:18 by ytop              #+#    #+#              #
#    Updated: 2024/03/15 15:26:37 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minitalk

SERVER			= server
CLIENT			= client

SRC_SV          = ./sources/server.c
SRC_CL          = ./sources/client.c

RM				= @rm -rf

CC				= @cc
FLAGS			= -Wall -Wextra -Werror

PRINTF_MAKE		= @make -C ./ft_printf

PRINTF			= ./ft_printf/libftprintf.a

COLOR_YELLOW	= \033[0;33m
COLOR_GREEN		= \033[0;32m
COLOR_RED		= \033[0;31m
COLOR_END		= \033[0m

all			:	$(NAME)

$(NAME)		:	$(SERVER) $(CLIENT)

$(SERVER)	:	$(SRC_SV)
				$(PRINTF_MAKE) all
				@echo "$(COLOR_YELLOW)Server Compiling...$(COLOR_END)"
				$(CC) $(FLAGS) -o $(SERVER) $(SRC_SV) $(PRINTF)
				@echo "Server: $(COLOR_GREEN)[OK]$(COLOR_END)\n"

$(CLIENT)	:	$(SRC_CL)
				@echo "$(COLOR_YELLOW)Client Compiling...$(COLOR_END)"
				$(CC) $(FLAGS) -o $(CLIENT) $(SRC_CL) $(PRINTF)
				@echo "Client: $(COLOR_GREEN)[OK]$(COLOR_END)\n"
				@echo "$(COLOR_GREEN)Finished.$(COLOR_END)"

clean		:
				$(PRINTF_MAKE) clean
				@echo "$(COLOR_RED)Object Files Removed!$(COLOR_END)\n"

fclean		:
				$(RM) $(SERVER) $(CLIENT)
				$(PRINTF_MAKE) fclean
				@echo "$(COLOR_RED)All Files Removed!$(COLOR_END)\n"

re			:	fclean all

.PHONY		:	all clean fclean re