# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:03:48 by ytop              #+#    #+#              #
#    Updated: 2024/09/30 13:06:47 by ytop             ###   ########.fr        #
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

SRCS			=	$(SRCS_DIR)ft_atoi.c		$(SRCS_DIR)ft_itoa.c		$(SRCS_DIR)ft_split.c		$(SRCS_DIR)ft_bzero.c		$(SRCS_DIR)ft_calloc.c	\
					$(SRCS_DIR)ft_memchr.c		$(SRCS_DIR)ft_memcmp.c		$(SRCS_DIR)ft_memcpy.c		$(SRCS_DIR)ft_memmove.c		$(SRCS_DIR)ft_memset.c	\
					$(SRCS_DIR)ft_strchr.c		$(SRCS_DIR)ft_strdup.c		$(SRCS_DIR)ft_substr.c		$(SRCS_DIR)ft_strjoin.c		$(SRCS_DIR)ft_strcmp.c	\
					$(SRCS_DIR)ft_strlcpy.c		$(SRCS_DIR)ft_strlen.c		$(SRCS_DIR)ft_strmapi.c		$(SRCS_DIR)ft_strncmp.c		$(SRCS_DIR)ft_strnstr.c	\
					$(SRCS_DIR)ft_strrchr.c		$(SRCS_DIR)ft_strtrim.c		$(SRCS_DIR)ft_isascii.c		$(SRCS_DIR)ft_tolower.c		$(SRCS_DIR)ft_toupper.c	\
					$(SRCS_DIR)ft_isalnum.c		$(SRCS_DIR)ft_isalpha.c		$(SRCS_DIR)ft_striteri.c	$(SRCS_DIR)ft_isdigit.c		$(SRCS_DIR)ft_isprint.c	\
					$(SRCS_DIR)ft_putchar_fd.c	$(SRCS_DIR)ft_putendl_fd.c	$(SRCS_DIR)ft_putnbr_fd.c	$(SRCS_DIR)ft_putstr_fd.c	$(SRCS_DIR)ft_strlcat.c	\
					

BONUS			=	$(BONUS_DIR)ft_lstadd_back_bonus.c	$(BONUS_DIR)ft_lstadd_front_bonus.c		\
					$(BONUS_DIR)ft_lstclear_bonus.c		$(BONUS_DIR)ft_lstdelone_bonus.c		\
					$(BONUS_DIR)ft_lstiter_bonus.c		$(BONUS_DIR)ft_lstlast_bonus.c			\
					$(BONUS_DIR)ft_lstsize_bonus.c		$(BONUS_DIR)ft_lstcopy_bonus.c			\
					$(BONUS_DIR)ft_lstsort_bonus.c		$(BONUS_DIR)ft_lstswap_bonus.c			\
					$(BONUS_DIR)ft_lstmap_bonus.c		$(BONUS_DIR)ft_lstnew_bonus.c			\

GC_SRCS			=	$(GARBAGE_DIR)garbage_collector.c	$(GARBAGE_DIR)garbage_collector_utils.c

PRINTF_SRCS		=	$(PRINT_DIR)ft_printf/ft_printf.c	$(PRINT_DIR)ft_printf/ft_printf_utils.c

DPRINTF_SRCS	=	$(PRINT_DIR)ft_dprintf/ft_dprintf.c	$(PRINT_DIR)ft_dprintf/ft_dprintf_utils.c

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS:.c=.o)

GC_OBJS			=	$(GC_SRCS:.c=.o)

GNL_OBJS		=	$(GNL_SRCS:.c=.o)

PLIST_OBJS		=	$(PLIST_SRCS:.c=.o)

PRINTF_OBJS		=	$(PRINTF_SRCS:.c=.o)
DPRINTF_OBJS	=	$(DPRINTF_SRCS:.c=.o)

CC				=	@cc
CFLAGS			=	-Wall -Wextra -Werror -I ../../includes

RM				=	@rm -rf

NAME			=	libft.a

PRINTF_MAKE		=	@make -C ./ft_printf
PRINTF_ARCHIVE	=	./ft_printf/libftprintf.a

COLOR_YELLOW	=	\033[0;33m
COLOR_GREEN		=	\033[0;32m
COLOR_RED		=	\033[0;31m
COLOR_END		=	\033[0m

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(BONUS_OBJS) $(GC_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(DPRINTF_OBJS) $(PLIST_OBJS)
					@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS) $(GC_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(DPRINTF_OBJS) $(PLIST_OBJS)
					@printf "LIBFT			$(COLOR_GREEN)\e[1m[OK]\e[0m\n$(COLOR_END)"

clean			:
					$(RM) $(OBJS) $(BONUS_OBJS) $(GC_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(DPRINTF_OBJS) $(PLIST_OBJS)

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all

bonus			:	$(BONUS_OBJS)
					@ar rcs $(NAME) $(BONUS_OBJS)

.PHONY			:	all clean fclean re bonus
