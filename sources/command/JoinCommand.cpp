/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:11 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 17:57:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"
#include "Server.hpp"
#include <iostream>
#include <sstream>

JoinCommand:: JoinCommand(Server& server) : _server(server) {}

JoinCommand::~JoinCommand() {}

void	JoinCommand::Execute(Client* sender, const Message& msg)
{
    // 1. Parametre Kontrolü
    if (msg.GetParameters().empty())
	{
        _server.SendsNumericReply(sender, 461, "JOIN :Not enough parameters"); // ERR_NEEDMOREPARAMS

        return ;
    }

    std::string channel_name	=  msg.GetParameters()[0];
    std::string channel_key		= (msg.GetParameters().size() > 1) ? msg.GetParameters()[1] : "";

    // Kanal adının geçerliliğini kontrol et (RFC 2812, Bölüm 1.3)
    // Kanal adları #, & gibi karakterlerle başlamalı ve boşluk, CTRL G, virgül içermemeli.
    if (channel_name.empty() || (channel_name[0] != '#' && channel_name[0] != '&'))
	{
        _server.SendsNumericReply(sender, 403, channel_name + " :No such channel"); // ERR_NOSUCHCHANNEL

        return ;
    }

    if (channel_name.find(' ') != std::string::npos ||
        channel_name.find(',') != std::string::npos ||
        channel_name.find(7) != std::string::npos) // CTRL+G (BEL)
    {
        _server.SendsNumericReply(sender, 403, channel_name + " :No such channel"); // ERR_NOSUCHCHANNEL

        return ;
    }

    Channel* channel = _server.FindChannel(channel_name);

    // 2. Kanalın Var Olup Olmadığı ve Oluşturma
    if (!channel) {
        // Kanal yoksa, yeni bir kanal oluştur
        channel = _server.CreateChannel(channel_name);
        // Yeni oluşturulan kanalın ilk üyesi otomatik olarak operatör olur (Channel sınıfında ayarlandı)
    } else {
        // Kanal varsa, mod kontrollerini yap
		// Kanal davetiyeliyse (+i modu), kullanıcı kanala katılamaz.
		// Şimdilik, davet mekanizmasını veya sunucu operatör bypass'ını implemente etmediğimiz için
		// sadece invite-only olup olmadığını kontrol ediyoruz.
        if (channel->IsInviteOnly()) {
    		_server.SendsNumericReply(sender, 473, channel_name + " :Cannot join channel (+i)"); // ERR_INVITEONLYCHAN
    		return;
		}
        if (!channel->GetPass().empty() && channel->GetPass() != channel_key) {
            _server.SendsNumericReply(sender, 475, channel_name + " :Cannot join channel (+k)"); // ERR_BADCHANNELKEY
            return;
        }
        if (channel->IsFull()) {
            _server.SendsNumericReply(sender, 471, channel_name + " :Cannot join channel (+l)"); // ERR_CHANNELISFULL
            return;
        }
        if (channel->IsUserInChannel(sender)) {
            // Kullanıcı zaten kanalda, bir şey yapmaya gerek yok, RFC'de bu bir hata değil.
            // Sadece debug çıktısı verelim.
            std::cout << "User " << sender->GetNickName() << " is already in channel " << channel_name << std::endl;
            return;
        }
    }

    // 3. Kullanıcıyı Kanala Ekle
    channel->AddUser(sender);

    channel->AddUser(sender); // Kanalın kullanıcı listesine ekle
    sender->AddChannel(channel); // Yeni: Kullanıcının kendi kanal listesine ekle

    // 4. Katılma Mesajını Kanala Yayınla
    // Format: :<nickname>!<username>@<hostname> JOIN :<channelname>
    std::stringstream join_msg_ss;
    join_msg_ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName()
                << " JOIN :" << channel_name;
    channel->BroadcastMessage(join_msg_ss.str()); // Mesajın sonuna CRLF eklemeyi broadcastMessage hallediyor

    // 5. Kanaldaki Kullanıcıya TOPIC ve NAMES Yanıtlarını Gönder
    // TOPIC (RPL_TOPIC 332)
    if (!channel->GetTopic().empty()) {
        _server.SendsNumericReply(sender, 332, channel_name + " :" + channel->GetTopic());
    } else {
        _server.SendsNumericReply(sender, 331, channel_name + " :No topic is set"); // RPL_NOTOPIC
    }

    // NAMES (RPL_NAMREPLY 353 ve RPL_ENDOFNAMES 366)
    std::stringstream names_ss;
    names_ss << "= " << channel_name << " :"; // = public kanal, @ secret, * private
    
    const std::map<int, Client*>& users_in_channel = channel->getUsers();
    const std::map<int, Client*>& ops_in_channel = channel->getOperators();

    bool first_user = true;
    for (std::map<int, Client*>::const_iterator it = users_in_channel.begin(); it != users_in_channel.end(); ++it) {
        if (!first_user) {
            names_ss << " ";
        }
        if (ops_in_channel.count(it->second->GetFD())) {
            names_ss << "@"; // Operatörler için prefix
        }
        names_ss << it->second->GetNickName();
        first_user = false;
    }
    _server.SendsNumericReply(sender, 353, names_ss.str()); // RPL_NAMREPLY
    _server.SendsNumericReply(sender, 366, channel_name + " :End of /NAMES list"); // RPL_ENDOFNAMES

    std::cout << "User " << sender->GetNickName() << " successfully joined channel " << channel_name << std::endl;
}
