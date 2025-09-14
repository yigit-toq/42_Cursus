NAME			=	ircserv

SRCS_DIR		=	./sources/
OBJS_DIR		=	./objects/

BONUS_DIR		=	${SRCS_DIR}bonus/
UTILS_DIR		=	${SRCS_DIR}utils/

PROCESS_DIR		=	${SRCS_DIR}process/
NETWORK_DIR		=	${SRCS_DIR}network/
COMMAND_DIR		=	${SRCS_DIR}command/

PROTOCOL_DIR	=	${SRCS_DIR}protocol/

M_SRCS 			=	$(SRCS_DIR)Main.cpp		$(COMMAND_DIR)UserCommand.cpp		$(PROCESS_DIR)Server.cpp		$(NETWORK_DIR)Socket.cpp			$(PROTOCOL_DIR)Message.cpp				$(UTILS_DIR)Utils.cpp	\
											$(COMMAND_DIR)QuitCommand.cpp		$(PROCESS_DIR)Client.cpp		$(NETWORK_DIR)PollHandler.cpp		$(PROTOCOL_DIR)CommandHandler.cpp		$(UTILS_DIR)Logger.cpp	\
											$(COMMAND_DIR)PrivCommand.cpp		$(PROCESS_DIR)Channel.cpp																											\
											$(COMMAND_DIR)PassCommand.cpp																																			\
											$(COMMAND_DIR)PartCommand.cpp																																			\
											$(COMMAND_DIR)NickCommand.cpp																																			\
											${COMMAND_DIR}ModeCommand.cpp																																			\
											$(COMMAND_DIR)KickCommand.cpp																																			\
											$(COMMAND_DIR)JoinCommand.cpp																																			\
											${COMMAND_DIR}TopicCommand.cpp																																			\
											${COMMAND_DIR}InviteCommand.cpp																																			\

M_OBJS 			=	$(patsubst $(SRCS_DIR)%.cpp,$(OBJS_DIR)%.o,$(M_SRCS))

RMRF			=	@rm -rf

CXX				=	@c++

CXXFLAGS		=	-Wall  -Wextra -Werror	\
					-I ./includes/protocol	\
					-I ./includes/command	\
					-I ./includes/network	\
					-I ./includes/process	\
					-I ./includes/utils		\
					-I ./includes/bonus		\

STD				=	-std=c++98

## BONUS

B_SRCS			=	$(BONUS_DIR)Assistant.cpp $(BONUS_DIR)Main.cpp

B_OBJS			=	$(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(B_SRCS:.cpp=.o))

ASST			=	assistant

LOGS			=	./irc_server.log

## COLOR

C_Y				=	\033[0;33m
C_G				=	\033[0;32m
C_R				=	\033[0;31m
C_E				=	\033[0m

$(OBJS_DIR)%.o	:	$(SRCS_DIR)%.cpp
					@mkdir -p	$(dir $@)
					$(CXX)		$(CXXFLAGS) $(STD) -c	$< -o $@

all				:	$(NAME)

bonus			:	$(ASST)

$(NAME)			:	$(M_OBJS)
					$(CXX)		$(CXXFLAGS) $(STD)		$^ -o $(NAME)
					@echo "\e[1m$(C_Y)IRCSERV		$(C_G)[OK]\e[0m$(C_E)"

$(ASST)			:	$(B_OBJS)
					$(CXX)		$(CXXFLAGS) $(STD)		$^ -o $(ASST)
					@echo "\e[1m$(C_Y)IRCASST		$(C_G)[OK]\e[0m$(C_E)"

clean			:
					$(RMRF)		$(OBJS_DIR)
					@echo "\e[1m$(C_Y)OBJECTS		$(C_R)[KO]\e[0m$(C_E)"
			

fclean			:	clean
					$(RMRF)		$(LOGS)
					$(RMRF)		$(NAME)
					$(RMRF)		$(ASST)
					@echo "\e[1m$(C_Y)EXECUTE		$(C_R)[KO]\e[0m$(C_E)"

re				:	fclean all

.PHONY			:	all bonus clean fclean re
