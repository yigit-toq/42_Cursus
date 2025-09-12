#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "Message.hpp"

class Client;

class CommandHandler
{
	private:
		CommandHandler					(const CommandHandler& other);
		CommandHandler& operator=		(const CommandHandler& other);

	public:
				 CommandHandler			();
		virtual ~CommandHandler			();

		virtual void Execute			(Client* sender, const Message& msg) = 0;
};

#endif
