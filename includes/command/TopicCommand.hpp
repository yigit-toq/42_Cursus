#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class TopicCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		TopicCommand			(const TopicCommand& other);
		TopicCommand& operator=	(const TopicCommand& other);

	public:
		 TopicCommand			(Server& server);
		~TopicCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
