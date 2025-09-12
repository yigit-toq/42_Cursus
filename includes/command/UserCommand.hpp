#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class UserCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		UserCommand				(const UserCommand& other);
		UserCommand& operator=	(const UserCommand& other);

	public:
		 UserCommand			(Server& server);
		~UserCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
