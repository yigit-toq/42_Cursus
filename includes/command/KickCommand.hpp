#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class KickCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		KickCommand				(const KickCommand& other);
		KickCommand& operator=	(const KickCommand& other);

	public:
		 KickCommand			(Server& server);
		~KickCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
