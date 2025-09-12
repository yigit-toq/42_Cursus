#include "Assistant.hpp"

Assistant::Assistant(const std::string& server_addr, int server_port, const std::string& password, const std::string& nickname)
			: _server_addr(server_addr), _server_port(server_port), _bot_socket(-1), _password(password), _nickname(nickname)
{
	std::srand(std::time(0));

	_quotes = {
		"1",
		"2",
		"3"
	};
}

void	Assistant::Start()
{
	try
	{
		ConnectToServer	();
		AuthAndRegister	();

		std::cout << "Waiting for an INVITE to join a channel..." << std::endl;

		MainLoop		();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	Close();
}

void	Assistant::Close()
{
	if (_bot_socket != -1)
	{
		SendMessage	("QUIT :Bot is shutting down\r\n");

		close		(_bot_socket);

		_bot_socket = -1;
	}
}

void	Assistant::SendMessage(const std::string& message)
{
	if (send(_bot_socket, message.c_str(), message.length(), 0) == -1)
	{
		throw std::runtime_error("Failed to send message: " + message);
	}
}

void	Assistant::ConnectToServer()
{
	_bot_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_bot_socket == -1)
	{
		throw std::runtime_error("Failed to create socket");
	}

	sockaddr_in	server_addr;

	server_addr.sin_family	= AF_INET				;
	server_addr.sin_port	= htons(_server_port)	;

	if (inet_pton(AF_INET, _server_addr.c_str(), &server_addr.sin_addr) <= 0)
	{
		throw std::runtime_error("Invalid address");
	}

	if (connect(_bot_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		throw std::runtime_error("Failed to connect to server");
	}

	std::cout << "Connected to server at " << _server_addr << ":" << _server_port << std::endl;
}

void	Assistant::AuthAndRegister()
{
	SendMessage("PASS " + _password + "\r\n");
	SendMessage("NICK " + _nickname + "\r\n");
	SendMessage("USER " + _nickname + " 0 * :" + _nickname + " bot\r\n");

	sleep(1);
}

void	Assistant::ProcessMessage(const std::string& full_message)
{
	std::vector<std::string> parts = Utils::split(full_message, ' ');

	if (parts.size() >= 2)
	{
		std::string sender_info = parts[0];
		std::string sender_nick = sender_info.substr(1, sender_info.find('!') - 1);
		
		if (parts[1] == "PRIVMSG")
		{
			std::string tar_channel = parts[2];
			std::string msg_content = full_message.substr(full_message.find(" :") + 2);

			HandlerCommand(sender_nick, tar_channel, msg_content);
		}
		else if (parts[1] == "JOIN")
		{
			if (sender_nick != _nickname)
			{
				std::string channel_name = parts[2].substr(1);
				std::string welcome_msg = "PRIVMSG " + channel_name + " :Welcome, " + sender_nick + "!\r\n";

				SendMessage(welcome_msg);
			}
		}
		else if (parts[1] == "INVITE")
		{
			std::string channel_to_join = parts[3].substr(1);
			std::string join_msg = "JOIN " + channel_to_join + "\r\n";
			SendMessage(join_msg);
			std::cout << "Invited to " << channel_to_join << ". Attempting to join..." << std::endl;
		}
	}
}

void	Assistant::HandlerCommand(const std::string& sender_nick, const std::string& tar_channel, const std::string& msg_content)
{
	std::string	reply = "PRIVMSG " + tar_channel + " :";

	if (msg_content.find("!time") == 0)
	{
		reply += "Current time and date: " + GetCurrTime() + "\r\n";
	}
	else if (msg_content.find("!quote")  == 0)
	{
		int	rand_index = std::rand() % _quotes.size();

		reply += _quotes[rand_index] + "\r\n";
	}
	else if (msg_content.find("!whoami") == 0)
	{
		std::string sender_host = Utils::split(Utils::split(msg_content, '@')[0], '!') [1];

		reply += sender_nick + " you are " + sender_host + ".\r\n";
	}
	else if (msg_content.find(_nickname) == 0)
	{
		reply += sender_nick + ", did you call me? What would you like to ask?\r\n";
	}
	SendMessage(reply);
}

void	Assistant::MainLoop()
{
	char		buffer[BUFFER_SIZE] = {0};

	std::string	incoming_data;

	while (true)
	{
		ssize_t bytes_read = recv(_bot_socket, buffer, BUFFER_SIZE - 1, 0);

		if (bytes_read > 0)
		{
			buffer[bytes_read]	 = '\0';

			incoming_data		+= buffer;

			size_t	pos;

			while ((pos = incoming_data.find("\r\n")) != std::string::npos)
			{
				std::string	full_message = incoming_data.substr(0, pos);

				incoming_data.erase	(0, pos + 2);

				ProcessMessage		(full_message);
			}
		}
		else if (bytes_read == 0)
		{
			std::cout << "Disconnected from server." << std::endl;
			break ;
		}
		else
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
			{
				throw std::runtime_error("Failed to receive data");
			}
		}
	}
}

std::string	Assistant::GetCurrTime()
{
	std::time_t	now = std::time		(0);

	struct tm*	ltm = std::localtime(&now);

	std::stringstream time_ss;

	time_ss << ltm->tm_hour << ":" << ltm->tm_min		<< ":" << ltm->tm_sec << " "
			<< ltm->tm_mday << "/" << ltm->tm_mon + 1	<< "/" << ltm->tm_year + 1900;

	return time_ss.str();
}
