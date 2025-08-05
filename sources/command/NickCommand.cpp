/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:20 by ytop              #+#    #+#             */
/*   Updated: 2025/08/05 21:57:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"

NickCommand:: NickCommand(Server& server) : _server(server) {}

NickCommand::~NickCommand() {}

void	NickCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().empty())
	{
		_server.SendsNumericReply(sender, 431, "No nickname given");
		return ;
	}

	std::string new_nick = msg.GetParameters()[0];

	if (new_nick.length() > 9)
	{
		new_nick = new_nick.substr(0, 9);
	}

	if (!_server.IsNicknameAvailable(new_nick) && new_nick != sender->GetNickname())
	{
		_server.SendsNumericReply	(sender, 433, new_nick + " :Nickname is already in use");
		return ;
	}

	if (sender->IsRegistered() && !sender->GetNickname().empty())
	{
		_server.RmvClient	(sender);
	}

	sender->SetNickname				(new_nick);
	
	_server.SendsNumericReply		(sender, 001, "Your nickname has been set to " + new_nick);

	_server.AddClient				(sender);

	if (sender->GetStatus() == UNREGISTERED)
	{
		sender->SetStatus(NICK_SET);
	}

	_server.CheckRegistration(sender);
}
