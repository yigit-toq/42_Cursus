#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class JoinCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		JoinCommand				(const JoinCommand& other);
		JoinCommand& operator=	(const JoinCommand& other);

	public:
		 JoinCommand			(Server& server);
		~JoinCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
