# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 17:02:40 by ytop              #+#    #+#              #
#    Updated: 2024/09/30 13:17:12 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

COMPILER_DIR	=	$(SRCS_DIR)0-compiler/

EXECUTOR_DIR	=	$(SRCS_DIR)1-executor/

REDIRECT_DIR	=	$(SRCS_DIR)2-redirect/

BUILTIN_DIR		=	$(SRCS_DIR)3-builtin/

DOLLAR_DIR		=	$(SRCS_DIR)4-dollar/

UTIL_DIR		=	$(SRCS_DIR)5-utils/

SRCS			=	$(SRCS_DIR)minishell.c $(COMPILER_DIR)lexer.c $(COMPILER_DIR)parser.c $(EXECUTOR_DIR)executor.c $(REDIRECT_DIR)redirect.c $(BUILTIN_DIR)echo.c $(BUILTIN_DIR)env.c $(BUILTIN_DIR)exit.c $(BUILTIN_DIR)pwd.c $(BUILTIN_DIR)unset.c $(DOLLAR_DIR)dollar.c $(DOLLAR_DIR)dollar_utils.c $(UTIL_DIR)utils.c $(UTIL_DIR)split.c $(UTIL_DIR)signal.c $(UTIL_DIR)check_line.c

OBJS			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror $(INCLUDES)

INCLUDES		=	-I ./includes

RM				=	@rm -rf

NAME			=	minishell

LIBFT_MAKE		=	@make -C ./libraries/libft
LIBFT			=	./libraries/libft/libft.a

RDFLAGS			=	-lreadline

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RDFLAGS)
					@printf "MINISHELL		$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END) \n"

$(OBJS_DIR)%.o	:	$(SRCS_DIR)%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					$(RM) $(OBJS_DIR)
					$(LIBFT_MAKE) clean
					@printf "OBJECT FILES		$(COLOR_RED)\e[1m[KO]\e[0m\n$(COLOR_END)"

fclean			:	clean
					$(RM) $(NAME)
					$(LIBFT_MAKE) fclean
					@printf "EXECUTABLE FILES	$(COLOR_RED)\e[1m[KO]\e[0m\n$(COLOR_END)"

re				:	fclean all

$(LIBFT)		:	
					$(LIBFT_MAKE) all

.PHONY			:	all clean fclean re