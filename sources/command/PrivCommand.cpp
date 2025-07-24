/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:20:24 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 21:46:46 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

PrivCommand:: PrivCommand(Server& server) : _server(server) {}

PrivCommand::~PrivCommand() {}

void	PrivCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().size() < 2)
	{
		_server.SendsNumericReply(sender, 461, "PRIVMSG :Not enough parameters");
		return ;
	}

	const std::string& tar_name = msg.GetParameters()[0];
	const std::string& msg_text = msg.GetParameters()[1];

	if (msg_text.empty())
	{
		_server.SendsNumericReply(sender, 412, " :No text to send");
		return ;
	}

	if (tar_name[0] == '#' || tar_name[0] == '&')
	{
		Channel* target_channel = _server.FinderChannel(tar_name);

		if (!target_channel)
		{
			_server.SendsNumericReply(sender, 403, tar_name + " :No such channel");
			return ;
		}

		if (!target_channel->IsUser(sender))
		{
			_server.SendsNumericReply(sender, 404, tar_name + " :Cannot send to channel");
			return ;
		}

		std::stringstream ss;

		ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName() << " PRIVMSG " << tar_name << " :" << msg_text;

		target_channel->BroadcastMessage(ss.str(), sender);

		std::cout << "PRIVMSG to channel " << tar_name << " from " << sender->GetNickName() << ": " << msg_text << std::endl;

	}
	else
	{
		Client* target_user = _server.FindUserByNickname(tar_name);

		if (!target_user)
		{
			_server.SendsNumericReply(sender, 401, tar_name + " :No such nick/channel");
			return ;
		}

		std::stringstream ss;

		ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName() << " PRIVMSG " << tar_name << ": " << msg_text;

		target_user->AppendToOuputBuffer(ss.str() + "\r\n");

		_server.GetPollHandler().SetEvents(target_user->GetFD(), POLLIN | POLLOUT);

		std::cout << "PRIVMSG to user " << tar_name << " from " << sender->GetNickName() << ": " << msg_text << std::endl;
	}
}
