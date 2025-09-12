#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class ModeCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		ModeCommand				(const ModeCommand& other);
		ModeCommand& operator=	(const ModeCommand& other);

	public:
		 ModeCommand			(Server& server);
		~ModeCommand			();

		void Execute			(Client* sender, const Message& msg);

		void HandleChannelMode	(Client* sender, const Message& msg);
		void HandleClientsMode	(Client* sender, const Message& msg);
};

#endif
