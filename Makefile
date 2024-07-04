# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 20:10:24 by ytop              #+#    #+#              #
#    Updated: 2024/07/04 20:10:11 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR				=	./sources/

SRCS			=	$(DIR)0-philo.c $(DIR)1-main.c $(DIR)2-utils.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror #-fsanitize=thread

RM				=	@rm -rf

NAME			=	philo

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

NUM_FILES		:=	$(words $(SRCS))
CURRENT_FILE	:=	0

define	PROGRESS_BAR
	$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "\rCompiling... [%-50s] %d%%" $$(for i in $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(NUM_FILES)))); do printf =; done) $$(($(CURRENT_FILE) * 100 / $(NUM_FILES)))
	@sleep 0.1
endef

%.o				:	%.c
					$(CC) $(CFLAGS) -c $< -o $@
					$(PROGRESS_BAR)

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
					@printf "$(COLOR_GREEN)\n"
					@printf " ____  _  _  __  __     __   ____   __  ____  _  _  ____  ____  ____  \n"; sleep 0.1
					@printf "(  _ \/ )( \(  )(  )   /  \ / ___) /  \(  _ \/ )( \(  __)(  _ \/ ___) \n"; sleep 0.1
					@printf " ) __/) __ ( )( / (_/\(  O )\___ \(  O )) __/) __ ( ) _)  )   /\___ \ \n"; sleep 0.1
					@printf "(__)  \_)(_/(__)\____/ \__/ (____/ \__/(__)  \_)(_/(____)(__\_)(____/ \n"; sleep 0.1
					@printf "$(COLOR_END)\n"
					@printf "PHILOSOPHERS	$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)\n"

clean			:
					$(RM) $(OBJS)
					@printf "\nPHILOSOPHERS	$(COLOR_RED)\e[1m[CLEANED]\e[0m\n$(COLOR_END)\n"

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
