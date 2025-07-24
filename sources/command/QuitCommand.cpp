/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:49:04 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:13:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

QuitCommand:: QuitCommand(Server& server) : _server(server) {}

QuitCommand::~QuitCommand() {}

void	QuitCommand::Execute(Client* sender, const Message& msg)
{
	std::string quit_message = "Client Quit";

	if (!msg.GetParameters().empty())
	{
		quit_message = msg.GetParameters()[0];
	}

	std::stringstream quit_ss;

	quit_ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName() << " QUIT: " << quit_message;

	std::string full_quit_msg = quit_ss.str();

	const std::vector<Channel*>&	joined_channels = sender->GetJoinedChannels();

	std::vector<Channel*>			channel_to_part = joined_channels;

	for (size_t i = 0; i < channel_to_part.size(); ++i)
	{
		Channel* channel = channel_to_part[i];

		if (channel)
		{
			channel->BroadcastMessage	(full_quit_msg, sender);

			channel->RmvClient			(sender);

			if (channel->IsEmpty())
			{
				_server.RemoveChannel(channel->GetName());

				std::cout << "Channel " << channel->GetName() << " is empty and removed." << std::endl;
			}
		}
	}

	_server.ClientDisconnection(sender->GetFD());

	std::cout << "Client " << sender->GetNickName() << " (" << sender->GetFD() << ") has quit with message: '" << quit_message << "'" << std::endl;
}
