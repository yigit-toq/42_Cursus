/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:20 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 08:13:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"

NickCommand:: NickCommand	(Server& server) : _server(server) {}

NickCommand::~NickCommand	() {}

void	NickCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().empty()) //
	{
		_server.SendsNumericReply(sender, 431, ":No nickname given");
		return ;
	}

	if (sender->IsAuthenticated() == false) //
	{
		_server.SendsNumericReply(sender, 451, "NICK: You have not authenticated yet"			);
		return ;
	}

	std::string new_nick = msg.GetParameters()[0];

	if (!_server.IsNicknameAvailable(new_nick) && new_nick != sender->GetNickname())
	{
		_server.SendsNumericReply	(sender, 433, new_nick + " :Nickname is already in use");
		return ;
	}

	if (sender->IsRegistered())
	{
		std::string old_nick = sender->GetNickname();

		_server.RmvClient(sender);

		sender->SetNickname(new_nick);

		_server.AddClient(sender);

		_server.BroadcastNicknameChange(sender, old_nick, new_nick);

		_server.SendsNumericReply(sender, 001, ":Your nickname has been changed to " + new_nick);
	}
	else
	{
		sender->SetNickname(new_nick);

		_server.AddClient(sender);

		_server.SendsNumericReply(sender, 001, ":Your nickname has been set to " + new_nick);

		_server.CheckRegistration(sender);
	}
}
