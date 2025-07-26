/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:09:59 by ytop              #+#    #+#             */
/*   Updated: 2025/07/26 03:50:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCommand.hpp"
#include "Channel.hpp"
#include <iostream>
#include <sstream>

ModeCommand:: ModeCommand(Server& server) : _server(server) {}

ModeCommand::~ModeCommand() {}

void	ModeCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().empty())
	{
		_server.SendsNumericReply(sender, 461, "MODE :Not enough parameters");
		return ;
	}

	std::string target_name = msg.GetParameters()[0];

	if (target_name[0] == '#' || target_name[0] == '&')
	{
		HandleChannelMode	(sender, msg);
	}
	else
	{
		HandleClientMode	(sender, msg);
	}
}

void	ModeCommand::HandleChannelMode(Client* sender, const Message& msg)
{
	std::string	channel_name	= msg.GetParameters()[0];
	Channel*	target_channel	= _server.FindChannel(channel_name);

	if (!target_channel)
	{
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return ;
	}

	if (!target_channel->IsUser(sender))
	{
		_server.SendsNumericReply(sender, 442, channel_name + " :You're not on that channel");
		return ;
	}

	if (msg.GetParameters().size() == 1)
	{
		std::string mode_str = target_channel->GetModeString();
		std::string mode_params = target_channel->GetModeParams();
		_server.SendsNumericReply(sender, 324, channel_name + " " + mode_str + (mode_params.empty() ? "" : " " + mode_params));
		return ;
	}

	std::string mode_string = msg.GetParameters()[1];
	std::vector<std::string> mode_args;

	for (size_t i = 2; i < msg.GetParameters().size(); ++i)
	{
		mode_args.push_back(msg.GetParameters()[i]);
	}

	target_channel->ApplyModes(sender, mode_string, mode_args, _server);

	std::cout << "Channel MODE command processed for " << channel_name << std::endl;
}

void	ModeCommand::HandleClientMode(Client* sender, const Message& msg)
{
	std::string target_nick = msg.GetParameters()[0];
	Client* target_user = _server.FindClient(target_nick);

	if (!target_user)
	{
		_server.SendsNumericReply(sender, 401, target_nick + " :No such nick");
		return ;
	}

	if (sender->GetFD() != target_user->GetFD())
	{
		_server.SendsNumericReply(sender, 502, ":Cant change mode for other users");
		return ;
	}

	if (msg.GetParameters().size() == 1)
	{
		_server.SendsNumericReply(sender, 221, target_user->GetModeString());
		return ;
	}

	std::string mode_string = msg.GetParameters()[1];

	target_user->ApplyModes(sender, mode_string, _server);

	std::cout << "User MODE command processed for " << target_nick << std::endl;
}
