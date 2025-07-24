/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:42:07 by ytop              #+#    #+#             */
/*   Updated: 2025/07/24 21:49:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TopicCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

//Commandlerde Broadcast islemi ortak oldugu icin ayri bir fonksiyon yapilacak
//ayni zamanda bakilacak

TopicCommand:: TopicCommand(Server& server) : _server(server) {}

TopicCommand::~TopicCommand() {}

void	TopicCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().empty())
	{
		_server.SendsNumericReply(sender, 461, "TOPIC :Not enough parameters");
		return ;
	}

	std::string	channel_name	= msg.		GetParameters()[0];

	Channel*	channel_tar		= _server.	FinderChannel(channel_name);

	if (!channel_tar)
	{
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return ;
	}

	if (!channel_tar->IsUser(sender))
	{
		_server.SendsNumericReply(sender, 442, channel_name + " :You're not on that channel");
		return ;
	}

	if (msg.GetParameters().size() == 1)
	{
		if (channel_tar->GetTopic().empty())
		{
			_server.SendsNumericReply(sender, 331, channel_name + " :No topic is set");
		}
		else
		{
			_server.SendsNumericReply(sender, 332, channel_name + " :" + channel_tar->GetTopic());
		}
	}
	else
	{
		std::string new_topic = msg.GetParameters()[1];

		if (channel_tar->IsTopicSetByOp() && !channel_tar->IsOperator(sender))
		{
			_server.SendsNumericReply(sender, 482, channel_name + " :You're not channel operator");
			return ;
		}

		channel_tar->SetTopic(new_topic);

		std::stringstream topic_ss;

		topic_ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName() << " TOPIC " << channel_name << " :" << new_topic;

		channel_tar->BroadcastMessage(topic_ss.str(), NULL);

		std::cout << "Client " << sender->GetNickName() << " set topic for channel " << channel_name << " to: '" << new_topic << "'" << std::endl;
	}
}
