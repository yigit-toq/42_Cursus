/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:20:24 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 21:46:46 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivCommand.hpp"
#include "Server.hpp" // IRCServer'ın tamamına erişmek için dahil et
#include <iostream>
#include <sstream> // Stringstream için

PrivCommand::PrivCommand(Server& server) : _server(server) {}

PrivCommand::~PrivCommand() {}

void PrivCommand::Execute(Client* sender, const Message& msg) {
    // 1. Parametre Kontrolü: Mesajı göndermek için yeterli parametre var mı?
    if (msg.GetParameters().size() < 2) {
        _server.SendsNumericReply(sender, 461, "PRIVMSG :Not enough parameters"); // ERR_NEEDMOREPARAMS (461)
        return;
    }

    const std::string& target_name = msg.GetParameters()[0];    // Mesajın gideceği hedef (kanal veya nick)
    const std::string& message_text = msg.GetParameters()[1];   // Mesajın içeriği

    // Mesaj metni boş olamaz (RFC 2812, Bölüm 3.3.1)
    if (message_text.empty()) {
        _server.SendsNumericReply(sender, 412, ":No text to send"); // ERR_NOTEXTTOSEND (412)
        return;
    }

    // 2. Hedefin Türünü Belirle: Kanal mı, Kullanıcı mı?
    if (target_name[0] == '#' || target_name[0] == '&') {
        // Hedef bir kanal
        Channel* target_channel = _server.FindChannel(target_name);

        // Kanal mevcut mu?
        if (!target_channel) {
            _server.SendsNumericReply(sender, 403, target_name + " :No such channel"); // ERR_NOSUCHCHANNEL (403)
            return;
        }

        // Gönderen kullanıcı kanalda mı?
        // IRC standartlarında bu zorunlu değildir, ancak iyi bir uygulamadır.
        if (!target_channel->IsUserInChannel(sender)) {
            _server.SendsNumericReply(sender, 404, target_name + " :Cannot send to channel"); // ERR_CANNOTSENDTOCHAN (404)
            return;
        }

        // Mesajı oluştur: :<sender_nick>!<sender_user>@<sender_host> PRIVMSG <channel_name> :<message_text>
        std::stringstream ss;
        ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName()
           << " PRIVMSG " << target_name << " :" << message_text;

        // Mesajı kanaldaki tüm kullanıcılara yayınla (gönderen hariç)
        // NOT: BroadcastMessage metodunun, her hedef kullanıcıya mesajı appendToOutputBuffer ile ekledikten sonra
        // o kullanıcının soketi için POLLOUT olayını da etkinleştirdiğinden emin olun.
        // (yani _server.GetPollHandler().SetEvents(target_user->GetFD(), POLLIN | POLLOUT); çağrısı orada yapılmalı)
        target_channel->BroadcastMessage(ss.str(), sender);

        std::cout << "PRIVMSG to channel " << target_name << " from " << sender->GetNickName() << ": " << message_text << std::endl;

    } else {
        // Hedef bir kullanıcı (nickname)
        Client* target_user = _server.FindUserByNickname(target_name);

        // Hedef kullanıcı mevcut mu?
        if (!target_user) {
            _server.SendsNumericReply(sender, 401, target_name + " :No such nick/channel"); // ERR_NOSUCHNICK (401)
            return;
        }

        // Mesajı oluştur: :<sender_nick>!<sender_user>@<sender_host> PRIVMSG <target_nick> :<message_text>
        std::stringstream ss;
        ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName()
           << " PRIVMSG " << target_name << " :" << message_text;

        // Mesajı hedef kullanıcının çıkış tamponuna ekle
        target_user->AppendToOuputBuffer(ss.str() + "\r\n"); // CRLF eklemeyi unutmayın

        // KRİTİK: Hedef kullanıcının soketinde yazma olayını (POLLOUT) etkinleştir.
        // Bu, sunucuya bu soketten veri göndermesi gerektiğini söyler.
        // _server.GetPollHandler() metodunuzun olması gerekiyor.
        _server.GetPollHandler().SetEvents(target_user->GetFD(), POLLIN | POLLOUT);

        std::cout << "PRIVMSG to user " << target_name << " from " << sender->GetNickName() << ": " << message_text << std::endl;
    }
}
