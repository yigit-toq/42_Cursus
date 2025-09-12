#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class InviteCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		InviteCommand				(const InviteCommand& other);
		InviteCommand& operator=	(const InviteCommand& other);

	public:
		 InviteCommand				(Server& server);
		~InviteCommand				();

		void Execute				(Client* sender, const Message& msg);
};

#endif
