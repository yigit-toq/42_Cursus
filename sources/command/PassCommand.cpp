/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:30:38 by ytop              #+#    #+#             */
/*   Updated: 2025/08/07 00:35:53 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"
#include "Server.hpp"

//bakılacak

PassCommand:: PassCommand	(Server& server) : _server(server) {}

PassCommand::~PassCommand	() {}

void	PassCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered()		)
	{
		_server.SendsNumericReply(sender, 462, "You may not reregister"		);
		return ;
	}
	if (msg.GetParameters().empty()	)
	{
		_server.SendsNumericReply(sender, 461, "PASS :Not enough parameters");
		return ;
	}

	std::string	password = msg.GetParameters()[0];

	if (password != _server.GetPassword())
	{
		_server.SendsNumericReply	(sender, 464, "Password incorrect");

		_server.ClientDisconnection	(sender->GetFD());

		return ;
	}

	sender->SetPassword			(password);

	std::cout << "User FD " << sender->GetFD() << " provided correct password." << std::endl;

	_server.CheckRegistration	(sender);
}
