/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:20 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:21:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"
#include "Server.hpp"

NickCommand:: NickCommand(Server& server) : _server(server) {}

NickCommand::~NickCommand() {}

void	NickCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered())
	{
		std::cout << "User " << sender->GetNickName() << " trying to change nick to: " << msg.GetParameters()[0] << std::endl;
	}
	else
	{
		std::cout << "Unregistered user FD " << sender->GetFD() << " attempting to set nick." << std::endl;
	}

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

	if (!_server.IsNicknameAvailable(new_nick) && new_nick != sender->GetNickName())
	{
		_server.SendsNumericReply(sender, 433, new_nick + " :Nickname is already in use");
		return ;
	}

	sender->SetNickName(new_nick);

	if (sender->GetStatus() == UNREGISTERED)
	{
		sender->SetStatus(NICK_SET);
	}

	std::cout << "User FD " << sender->GetFD() << " nickname set to: " << new_nick << std::endl;

	_server.CheckRegistration(sender);
}
