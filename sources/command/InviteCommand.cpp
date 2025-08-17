/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:10:39 by ytop              #+#    #+#             */
/*   Updated: 2025/08/17 23:10:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCommand.hpp"
#include "Server.hpp"

InviteCommand:: InviteCommand	(Server& server) : _server(server) {}

InviteCommand::~InviteCommand	() {}

void InviteCommand::Execute		(Client* sender, const Message& msg)
{
	if (msg.GetParameters().size() < 2)
	{
		_server.SendsNumericReply(sender, 461, "INVITE :Not enough parameters");
		return ;
	}

	std::string target_nick = msg.GetParameters()[0];
	std::string channel_name = msg.GetParameters()[1];

	Channel* channel_tar = _server.FinderChannel(channel_name);
	Client* target_client = _server.FindClient(target_nick);

	// 1. Kanal var mı?
	if (!channel_tar) {
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return;
	}

	// 2. Davet eden kanalda mı?
	if (!channel_tar->IsUser(sender)) {
		_server.SendsNumericReply(sender, 442, channel_name + " :You're not on that channel");
		return;
	}

	// 3. Davet edilen kişi var mı?
	if (!target_client) {
		_server.SendsNumericReply(sender, 401, target_nick + " :No such nick/channel"); //
		return;
	}

	// 4. Kanal +i modundaysa davet eden op mu?
	if (channel_tar->IsModeSet('i') && !channel_tar->IsOperator(sender)) {
		_server.SendsNumericReply(sender, 482, channel_name + " :You're not channel operator");
		return;
	}

	// 5. Her şey yolundaysa daveti gönder
	// Davet eden kişiye onay mesajı (RPL_INVITING) gönder
	_server.SendsNumericReply(sender, 341, ":" + target_nick + " " + channel_name);

	// Davet edilen kişiye INVITE mesajını gönder
	std::string invite_msg = ":" + sender->GetNickname() + " INVITE " + target_nick + " :" + channel_name + "\r\n";

	channel_tar->AddInvitedUser(target_nick); //

	target_client->AppendToOuputBuffer(invite_msg);
	_server.GetPollHandler().SetEvents(target_client->GetFD(), POLLIN | POLLOUT);
}
