#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <csignal>
#include <string>
#include <vector>
#include <cerrno>
#include <ctime>

#include "../../includes/utils/Utils.hpp"

const int	BUFFER_SIZE = 1024;

typedef struct sockaddr		sockaddr;
typedef struct sockaddr_in	sockaddr_in;

class Assistant
{
	public:
		Assistant	(const std::string& server_ip, int server_port, const std::string& password, const std::string& nickname);

		void Start	();

		void Close	();

	private:
		std::string					_server_addr;

		int							_server_port;

		int							_bot_socket	;

		std::string					_password	;
		std::string					_nickname	;

		std::vector<std::string>	_quotes		;

		std::string	GetCurrTime		();

		void		SendMessage		(const std::string& message);

		void		ConnectToServer	();
		void		AuthAndRegister	();

		void		ProcessMessage	(const std::string& full_message);

		void		HandlerCommand	(const std::string& sender_nick, const std::string& target_channel, const std::string& message_content);

		void		MainLoop		();
};

static Assistant*	bot_instance = nullptr;

#endif
