/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:49:04 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 05:56:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

//bakılacak

QuitCommand:: QuitCommand	(Server& server) : _server(server) {}

QuitCommand::~QuitCommand	() {}

void	QuitCommand::Execute(Client* sender, const Message& msg)
{
	std::string quit_message = "Client Quit";

	if (!msg.GetParameters().empty())
	{
		quit_message = msg.GetParameters()[0];
	}

	std::stringstream	quit_ss;

	quit_ss << ":" << sender->GetNickname() << "!" << sender->GetUsername() << "@" << sender->GetHostname() << " QUIT: " << quit_message;

	std::string			quit_ms = quit_ss.str();

	const std::vector<Channel*>&	joined_channels = sender->GetJoinChannels();

	std::vector<Channel*>			channel_to_part = joined_channels;

	for (size_t i = 0; i < channel_to_part.size(); ++i)
	{
		Channel* channel = channel_to_part[i];

		if (channel)
		{
			channel->BroadcastMessage	(quit_ms, sender);

			channel->RmvClient			(sender);

			if (channel->IsEmpty		())
			{
				_server.RemoveChannel	(  channel->GetName());

				std::cout << "Channel " << channel->GetName() << " is empty and removed." << std::endl;
			}
		}
	}

	std::cout << "Client " <<	sender->GetNickname() << " (" << sender->GetFD() << ") has quit with message: '" << quit_message << "'" << std::endl;

	_server.ClientDisconnection(sender->GetFD());
}
