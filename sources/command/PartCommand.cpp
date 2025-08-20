/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:47:43 by ytop              #+#    #+#             */
/*   Updated: 2025/08/07 00:17:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

PartCommand:: PartCommand	(Server& server) : _server(server) {}

PartCommand::~PartCommand	() {}

void	PartCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().empty())
	{
		_server.SendsNumericReply(sender, 461, "PART :Not enough parameters");
		return ;
	}

	std::string name_strings	= msg.GetParameters()[0];

	std::string part_message	= "";

	if (msg.GetParameters().size() > 1)
	{
		part_message = msg.GetParameters()[1];
	}

	std::stringstream	ss(name_strings);
	std::string			channel_name;

	while (std::getline(ss, channel_name, ','))
	{
		if (channel_name.empty() ||		(channel_name[0] != '#' && channel_name[0] != '&'))
		{
			_server.SendsNumericReply	(sender, 403, channel_name + " :No such channel");
			continue ;
		}

		Channel* target_channel = _server.FinderChannel(channel_name);

		if (!target_channel)
		{
			_server.SendsNumericReply	(sender, 403, channel_name + " :No such channel");
			continue ;
		}

		if (!target_channel->IsUser		(sender))
		{
			_server.SendsNumericReply	(sender, 442, channel_name + " :You're not on that channel");
			continue ;
		}

		std::stringstream part_ss;

		part_ss << ":" << sender->GetNickname() << "!" << sender->GetUsername() << "@" << sender->GetHostname() << " PART " << channel_name;

		if (!part_message.empty())
		{
			part_ss << " :" << part_message;
		}

		target_channel->BroadcastMessage(part_ss.str(), NULL);

		target_channel->RmvClient		(sender);

		Logger::getInstance().Log(INFO, "User " + sender->GetNickname() + " parted from channel " + channel_name);

		if (target_channel->IsEmpty	())
		{
			_server.RemoveChannel	(target_channel->GetName());

			Logger::getInstance().Log(INFO, "Channel " + channel_name + " is empty and removed.");
		}
	}
}
