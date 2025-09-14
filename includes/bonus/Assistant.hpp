#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include "Server.hpp"

typedef struct sockaddr_in	sockaddr_in;
typedef struct sockaddr		sockaddr;

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

		std::string					GetCurrTime		();

		void						SendMessage		(const std::string& message);

		void						ConnectToServer	();
		void						AuthAndRegister	();

		void						ProcessMessage	(const std::string& full_message);

		void						HandlerCommand	(const std::string& sender_nick, const std::string& target_channel, const std::string& message_content);

		void						MainLoop		();

		std::vector<std::string>	Split			(const std::string& str, char delimiter);
};

static Assistant*	bot_instance = NULL;

#endif
