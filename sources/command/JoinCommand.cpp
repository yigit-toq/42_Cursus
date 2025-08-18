/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:11 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 05:05:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

//bakılacak

JoinCommand:: JoinCommand	(Server& server) : _server(server) {}

JoinCommand::~JoinCommand	() {}

void	JoinCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered() == false) //
	{
		_server.SendsNumericReply(sender, 451, ":You have not registered yet");
		return ;
	}
	if (msg.GetParameters().empty()) //
	{
		_server.SendsNumericReply(sender, 461, "JOIN :Not enough parameters" );

		return ;
	}

	std::string channel_name	=  msg.GetParameters()[0];
	std::string channel_key		= (msg.GetParameters().size() > 1) ? msg.GetParameters()[1] : "";


	if (channel_name.empty() || (channel_name[0] != '#' && channel_name[0] != '&'))
	{
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return ;
	}

	if (channel_name.find(' ') != std::string::npos ||
		channel_name.find(',') != std::string::npos || channel_name.find(7) != std::string::npos)
	{
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return ;
	}

	Channel* channel;

	channel = _server.FinderChannel(channel_name);

	if (!channel)
	{
		channel = _server.CreateChannel(channel_name);
	}
	else
	{
		if (!channel->GetPass().empty() && channel->GetPass() != channel_key)
		{
			_server.SendsNumericReply(sender, 475, channel_name + " :Cannot join channel (+k)");
			return ;
		}
		if (channel->IsModeSet('i')) //
		{
			if (channel->IsUserInvited(sender->GetNickname()) == false)
			{
				_server.SendsNumericReply(sender, 473, channel_name + " :Cannot join channel (+i)");
				return ;
			}
			channel->RmvInvitedUser(sender->GetNickname());
		}
		if (channel->IsFull			 ())
		{
			_server.SendsNumericReply(sender, 471, channel_name + " :Cannot join channel (+l)");
			return ;
		}

		if (channel->IsUser			 (sender))
		{
			std::cout << "User " <<  sender->GetNickname() << " is already in channel " << channel_name << std::endl;
			return ;
		}
	}

	channel	->AddClient	(sender	);
	sender	->AddChannel(channel);

	std::stringstream join_msg_ss;

	join_msg_ss << ":" << sender->GetNickname() << "!" << sender->GetUsername() << "@" << sender->GetHostname() << " JOIN :" << channel_name;

	channel->BroadcastMessage(join_msg_ss.str());

	if (!channel->GetTopic().empty())
	{
		_server.SendsNumericReply(sender, 332, channel_name + " :" + channel->GetTopic());
	}
	else
	{
		_server.SendsNumericReply(sender, 331, channel_name + " :No topic is set");
	}

	std::stringstream names_ss;

	names_ss << "= " << channel_name << " :";
	
	const std::map<int, Client*>& users_in_channel		= channel->GetUsers		();
	const std::map<int, Client*>& operators_in_channel	= channel->GetOperators	();

	bool first_user = true;

	for (std::map<int, Client*>::const_iterator it = users_in_channel.begin(); it != users_in_channel.end(); ++it)
	{
		if (!first_user)
		{
			names_ss << " ";
		}
		if (operators_in_channel.count(it->second->GetFD()))
		{
			names_ss << "@";
		}

		names_ss << it->second->GetNickname();

		first_user = false;
	}

	_server.SendsNumericReply(sender, 353, names_ss.str());
	_server.SendsNumericReply(sender, 366, channel_name + " :End of /NAMES list");

	std::cout << "User " << sender->GetNickname() << " successfully joined channel " << channel_name << std::endl;
}
