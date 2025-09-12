#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class QuitCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		QuitCommand				(const QuitCommand& other);
		QuitCommand& operator=	(const QuitCommand& other);

	public:
		 QuitCommand			(Server& server);
		~QuitCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
