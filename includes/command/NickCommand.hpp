#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class NickCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		NickCommand				(const NickCommand& other);
		NickCommand& operator=	(const NickCommand& other);

	public:
		 NickCommand			(Server& server);
		~NickCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
