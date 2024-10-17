# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:03:48 by ytop              #+#    #+#              #
#    Updated: 2024/10/17 13:56:46 by ytop             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR			=	./sources/mandatory/

BONUS_DIR			=	./sources/bonus/

PLIST_DIR			=	./utils/0-plist/

PRINT_DIR			=	./utils/1-printf/

GARBAGE_DIR			=	./utils/2-garbage/

GET_NEXT_LINE_DIR	=	./utils/3-get_next_line/

PLIST_SRCS			=	$(PLIST_DIR)plist.c

GNL_SRCS			=	$(GET_NEXT_LINE_DIR)get_next_line.c

SRCS				=	$(SRCS_DIR)ft_atoi.c		$(SRCS_DIR)ft_itoa.c		$(SRCS_DIR)ft_split.c		$(SRCS_DIR)ft_bzero.c		$(SRCS_DIR)ft_calloc.c	\
						$(SRCS_DIR)ft_memchr.c		$(SRCS_DIR)ft_memcmp.c		$(SRCS_DIR)ft_memcpy.c		$(SRCS_DIR)ft_memmove.c		$(SRCS_DIR)ft_memset.c	\
						$(SRCS_DIR)ft_strchr.c		$(SRCS_DIR)ft_strdup.c		$(SRCS_DIR)ft_substr.c		$(SRCS_DIR)ft_strjoin.c		$(SRCS_DIR)ft_strcmp.c	\
						$(SRCS_DIR)ft_strlcpy.c		$(SRCS_DIR)ft_strlen.c		$(SRCS_DIR)ft_strmapi.c		$(SRCS_DIR)ft_strncmp.c		$(SRCS_DIR)ft_strnstr.c	\
						$(SRCS_DIR)ft_strrchr.c		$(SRCS_DIR)ft_strtrim.c		$(SRCS_DIR)ft_isascii.c		$(SRCS_DIR)ft_tolower.c		$(SRCS_DIR)ft_toupper.c	\
						$(SRCS_DIR)ft_isalnum.c		$(SRCS_DIR)ft_isalpha.c		$(SRCS_DIR)ft_striteri.c	$(SRCS_DIR)ft_isdigit.c		$(SRCS_DIR)ft_isprint.c	\
						$(SRCS_DIR)ft_putchar_fd.c	$(SRCS_DIR)ft_putendl_fd.c	$(SRCS_DIR)ft_putnbr_fd.c	$(SRCS_DIR)ft_putstr_fd.c	$(SRCS_DIR)ft_strlcat.c	\

BONUS				=	$(BONUS_DIR)ft_lstmap_bonus.c							$(BONUS_DIR)ft_lstnew_bonus.c													\
						$(BONUS_DIR)ft_lstsort_bonus.c							$(BONUS_DIR)ft_lstlast_bonus.c													\
						$(BONUS_DIR)ft_lstsize_bonus.c							$(BONUS_DIR)ft_lstswap_bonus.c													\
						$(BONUS_DIR)ft_lstiter_bonus.c							$(BONUS_DIR)ft_lstcopy_bonus.c													\
						$(BONUS_DIR)ft_lstclear_bonus.c							$(BONUS_DIR)ft_lstdelone_bonus.c												\
						$(BONUS_DIR)ft_lstadd_back_bonus.c						$(BONUS_DIR)ft_lstadd_front_bonus.c												\

GC_SRCS				=	$(GARBAGE_DIR)garbage_collector.c	$(GARBAGE_DIR)garbage_collector_utils.c

PRINTF_SRCS			=	$(PRINT_DIR)ft_printf/ft_printf.c	$(PRINT_DIR)ft_printf/ft_printf_utils.c

DPRINTF_SRCS		=	$(PRINT_DIR)ft_dprintf/ft_dprintf.c	$(PRINT_DIR)ft_dprintf/ft_dprintf_utils.c

OBJS 				=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))			\
						$(patsubst %.c, $(OBJS_DIR)/%.o, $(GC_SRCS)) 		\
						$(patsubst %.c, $(OBJS_DIR)/%.o, $(GNL_SRCS)) 		\
						$(patsubst %.c, $(OBJS_DIR)/%.o, $(PLIST_SRCS)) 	\
						$(patsubst %.c, $(OBJS_DIR)/%.o, $(PRINTF_SRCS)) 	\
						$(patsubst %.c, $(OBJS_DIR)/%.o, $(DPRINTF_SRCS))	\

BONUS_OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(BONUS))

RM					=	@rm -rf

CC					=	@cc
CFLAGS				=	-Wall -Wextra -Werror -I ../../includes/utils

NAME				=	libft.a

OBJS_DIR 			=	./objects

COLOR_END			=	\033[0m
COLOR_RED			=	\033[0;31m
COLOR_GREEN			=	\033[0;32m
COLOR_YELLOW		=	\033[0;33m
COLOR_BLUE			=	\033[0;34m

total_files			:=	$(words $(SRCS) $(BONUS) $(GC_SRCS) $(GNL_SRCS) $(PLIST_SRCS) $(PRINTF_SRCS) $(DPRINTF_SRCS))

counter 			=	0

progress_bar 		=	@$(eval counter=$(shell echo $$(( $(counter) + 1 )))) \
						@percent=$$(( 100 * $(counter) / $(total_files) )); \
						printf "$(COLOR_BLUE)\rCompiling:	$(COLOR_YELLOW)%-44s $(COLOR_GREEN)\e[1m[%2d%%]\e[0m$(COLOR_END)" $< $$percent

all					:	$(NAME)

bonus				:	$(BONUS_OBJS)
						@ar rcs $(NAME) $(BONUS_OBJS)

$(NAME)				:	$(OBJS) $(BONUS_OBJS)
						@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
						@printf "\r%-80s\r" " "
						@printf "$(COLOR_BLUE)LIBFT			$(COLOR_GREEN)\e[1m[ OK ]\e[0m\n$(COLOR_END)"

$(OBJS_DIR)/%.o		: 	%.c
						@mkdir -p $(dir $@)
						$(CC) $(CFLAGS) -c $< -o $@
						$(progress_bar)

re					:	fclean all

clean				:
						$(RM) $(OBJS_DIR)
						$(RM) .progress

fclean				:	clean
						$(RM) $(NAME)

.PHONY				:	all bonus re clean fclean
