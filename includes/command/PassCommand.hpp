#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class PassCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		PassCommand				(const PassCommand& other);
		PassCommand& operator=	(const PassCommand& other);

	public:
		 PassCommand			(Server& server);
		~PassCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
