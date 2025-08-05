/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:29:44 by ytop              #+#    #+#             */
/*   Updated: 2025/08/05 21:04:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

KickCommand:: KickCommand(Server& server) : _server(server) {}

KickCommand::~KickCommand() {}

void	KickCommand::Execute(Client* sender, const Message& msg)
{
	std::cout << "geldi" << std::endl;

	if (msg.GetParameters().size() < 2)
	{
		_server.SendsNumericReply(sender, 461, "KICK :Not enough parameters");
		return ;
	}

	std::cout << "geldi1" << std::endl;

	std::string channel_name = msg.GetParameters()[0];
	std::string kicked_user_name = msg.GetParameters()[1];
	std::string reason = (msg.GetParameters().size() > 2) ? msg.GetParameters()[2] : kicked_user_name;

	Channel* channel = _server.FinderChannel(channel_name);
	if (!channel) {
		_server.SendsNumericReply(sender, 403, channel_name + " :No such channel");
		return;
	}

	std::cout << "geldi2" << std::endl;
	std::cout << "kicked_user_name: " << kicked_user_name << std::endl;

	Client* kicked_user = _server.FindClient(kicked_user_name);
	if (!kicked_user) {
		_server.SendsNumericReply(sender, 401, kicked_user_name + " :No such nick");
		return;
	}

	std::cout << "geldi3" << std::endl;
	
	// Yetki kontrolü: Sadece kanal operatörü kick atabilir.
	if (!channel->IsOperator(sender)) {
		_server.SendsNumericReply(sender, 482, channel_name + " :You're not channel operator");
		return;
	}

	std::cout << "geldi4" << std::endl;

	// Atılacak kullanıcının kanalda olup olmadığını kontrol et.
	if (!channel->IsUser(kicked_user)) {
		_server.SendsNumericReply(sender, 441, kicked_user_name + " " + channel_name + " :They are not on that channel");
		return;
	}

	std::cout << "geldi5" << std::endl;

	// Kick atma işlemi ve mesajı kanala yayınlama.
	// IRC'nin standart KICK mesaj formatı: KICK <kanal> <kullanıcı> :<sebep>
	_server.BroadcastChannelMessage(channel, sender, "KICK " + channel_name + " " + kicked_user_name + " :" + reason);
	
	// Kullanıcıyı kanaldan çıkar.
	channel->RmvClient(kicked_user);
}
