#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class PartCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		PartCommand				(const PartCommand& other);
		PartCommand& operator=	(const PartCommand& other);

	public:
		 PartCommand			(Server& server);
		~PartCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
