/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:47:43 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:13:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCommand.hpp"
#include "Server.hpp"
#include <sstream> // std::stringstream için
#include <iostream> // Debug çıktıları için

PartCommand::PartCommand(Server& server) : _server(server) {}

PartCommand::~PartCommand() {}

void PartCommand::Execute(Client* sender, const Message& msg) {
    // 1. Parametre Kontrolü: En az bir kanal adı olmalı
    if (msg.GetParameters().empty()) {
        _server.SendsNumericReply(sender, 461, "PART :Not enough parameters"); // ERR_NEEDMOREPARAMS (461)
        return;
    }

    // Kanal listesini al (virgülle ayrılmış olabilir)
    std::string channel_names_str = msg.GetParameters()[0];
    std::string part_message = ""; // Ayrılma mesajı (isteğe bağlı)

    // Eğer ayrılma mesajı varsa, onu al
    if (msg.GetParameters().size() > 1) {
        part_message = msg.GetParameters()[1];
    }

    // Kanal isimlerini ayrıştır (virgülle ayrılmış olabilir)
    std::stringstream ss(channel_names_str);
    std::string channel_name;

    while (std::getline(ss, channel_name, ',')) {
        // Kanal adının geçerli bir IRC kanalı formatında olduğundan emin ol (örn. # veya & ile başlar)
        if (channel_name.empty() || (channel_name[0] != '#' && channel_name[0] != '&')) {
            // Geçersiz kanal adı formatı için özel bir hata kodu yok, genellikle ERR_NOSUCHCHANNEL kullanılır.
            _server.SendsNumericReply(sender, 403, channel_name + " :No such channel"); // ERR_NOSUCHCHANNEL (403)
            continue; // Sonraki kanala geç
        }

        Channel* target_channel = _server.FindChannel(channel_name);

        // 2. Hata Kontrolü: Kanal mevcut mu?
        if (!target_channel) {
            _server.SendsNumericReply(sender, 403, channel_name + " :No such channel"); // ERR_NOSUCHCHANNEL (403)
            continue; // Sonraki kanala geç
        }

        // 3. Hata Kontrolü: Kullanıcı kanalda mı?
        if (!target_channel->IsUserInChannel(sender)) {
            _server.SendsNumericReply(sender, 442, channel_name + " :You're not on that channel"); // ERR_NOTONCHANNEL (442)
            continue; // Sonraki kanala geç
        }

        // 4. Kullanıcıyı kanaldan çıkar ve PART mesajını yayınla
        // Format: :<sender_nick>!<sender_user>@<sender_host> PART <channel_name> :<part_message>
        std::stringstream part_ss;
        part_ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName()
                << " PART " << channel_name;
        if (!part_message.empty()) {
            part_ss << " :" << part_message;
        }

        // Kanalın tüm üyelerine (ayrılan kişi dahil) PART mesajını yayınla
        // RFC'ye göre ayrılan kişi de kendi PART mesajını görmelidir.
        target_channel->BroadcastMessage(part_ss.str(), NULL); // NULL, herkesin görmesi için

        // Kullanıcıyı kanaldan gerçekten çıkar
        target_channel->RmvUser(sender); // Bu metodu Channel sınıfına eklemeniz gerekecek

        // Kullanıcının da kendi kanal listesinden bu kanalı çıkarması gerekebilir.
        // Bu, Client sınıfında bir metotla yönetilebilir (örn. Client::RemoveChannel(Channel*)).
        // sender->RemoveChannel(target_channel); // Bu metodu Client sınıfına eklemeniz gerekecek

        std::cout << "Client " << sender->GetNickName() << " parted from channel " << channel_name << std::endl;

        // 5. Kanal boşaldıysa, kanalı sil (isteğe bağlı ama iyi pratik)
        if (target_channel->IsEmpty()) { // IsEmpty() metodu Channel sınıfında olmalı
            _server.RemoveChannel(target_channel->GetName()); // Bu metodu IRCServer sınıfına eklemeniz gerekecek
            std::cout << "Channel " << channel_name << " is empty and removed." << std::endl;
        }
    }
}
