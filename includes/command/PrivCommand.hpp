#ifndef PRIVCOMMAND_HPP
#define PRIVCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class PrivCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		PrivCommand				(const PrivCommand& other);
		PrivCommand& operator=	(const PrivCommand& other);

	public:
		 PrivCommand			(Server& server);
		~PrivCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
