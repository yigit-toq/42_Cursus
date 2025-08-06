/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:29:44 by ytop              #+#    #+#             */
/*   Updated: 2025/08/07 00:04:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

//bakılacak

KickCommand:: KickCommand	(Server& server) : _server(server) {}

KickCommand::~KickCommand	() {}

void	KickCommand::Execute(Client* sender, const Message& msg)
{
	if (msg.GetParameters().size() < 2)
	{
		_server.SendsNumericReply(sender, 461, "KICK :Not enough parameters");
		return ;
	}

	std::string chnl_name	= msg.GetParameters()[0];
	std::string user_name	= msg.GetParameters()[1];

	std::string reason		= (msg.GetParameters().size() > 2) ? msg.GetParameters()[2] : user_name;

	Channel*	chnl;
	Client*		user;

	if (!(chnl = _server.FinderChannel	(chnl_name)))
	{
		_server.SendsNumericReply(sender, 403, chnl_name + " :No such channel"	);
		return ;
	}
	if (!(user = _server.FindClient		(user_name)))
	{
		_server.SendsNumericReply(sender, 401, user_name + " :No such nick"		);
		return ;
	}

	if (!chnl->IsOperator	(sender))
	{
		_server.SendsNumericReply(sender, 482, chnl_name + " :You're not channel operator");
		return ;
	}

	if (!chnl->IsUser		(user)	)
	{
		_server.SendsNumericReply(sender, 441, user_name + " " + chnl_name + " :They are not on that channel");
		return ;
	}

	_server.BroadcastChannelMessage	(chnl, sender, "KICK " + chnl_name + " " + user_name + " :" + reason);
	
	chnl->RmvClient					(user);
}
