/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:49:04 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:13:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCommand.hpp"
#include "Server.hpp"
#include <sstream>
#include <iostream>

QuitCommand::QuitCommand(Server& server) : _server(server) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::Execute(Client* sender, const Message& msg) {
    std::string quit_message = "Client Quit"; // Varsayılan çıkış mesajı

    // Eğer kullanıcı bir ayrılma mesajı belirtmişse
    if (!msg.GetParameters().empty()) {
        quit_message = msg.GetParameters()[0];
    }

    // 1. Kullanıcının bulunduğu tüm kanallara QUIT mesajını yayınla
    // Bunun için Client nesnesinin hangi kanallarda olduğunu bilmesi gerekir.
    // Eğer Client sınıfınızda _joined_channels gibi bir liste tutmuyorsanız,
    // IRCServer'ın tüm kanallarını iterate edip, her kanalda bu kullanıcının olup olmadığını kontrol etmeniz gerekecek.
    // VEYA, daha verimli bir yaklaşım olarak, Client sınıfına bir _joined_channels listesi eklemelisiniz.
    // Şimdilik, Client'ın _joined_channels listesini tuttuğunu varsayalım.

    // Eğer Client sınıfınızda getJoinedChannels() gibi bir metot yoksa,
    // aşağıdaki döngüyü buna göre düzenlemeniz veya Client sınıfını güncellemeniz gerekecek.

    // QUIT mesajı formatı: :<nick>!<user>@<host> QUIT :<quit_message>
    std::stringstream quit_ss;
    quit_ss << ":" << sender->GetNickName() << "!" << sender->GetUserName() << "@" << sender->GetHostName()
            << " QUIT :" << quit_message;
    std::string full_quit_msg = quit_ss.str();

    // Kullanıcının katıldığı her kanalda bu QUIT mesajını yayınla
    // Bu kısım, Client sınıfınızın kanalları nasıl yönettiğine bağlıdır.
    // Varsayım: Client'ta Channel* objelerini tutan bir liste var.
    const std::vector<Channel*>& joined_channels = sender->GetJoinedChannels(); // Yeni metot varsayımı

    // Iteratörü kullanırken dikkatli olun, kanaldan kullanıcı silineceği için
    // aynı anda koleksiyonu modify etmek sorun yaratabilir.
    // Bu nedenle bir kopya üzerinde iterate etmek daha güvenlidir.
    std::vector<Channel*> channels_to_part = joined_channels; // Geçici kopya

    for (size_t i = 0; i < channels_to_part.size(); ++i) {
        Channel* channel = channels_to_part[i];
        if (channel) {
            // Kullanıcının kanaldan çıkarıldığını gösteren QUIT mesajını diğer üyelere yayınla
            channel->BroadcastMessage(full_quit_msg, sender); // Gönderen hariç

            // Kullanıcıyı kanaldan tamamen çıkar
            channel->RmvUser(sender);

            // Kanal boşaldıysa, kanalı sunucudan sil
            if (channel->IsEmpty()) {
                _server.RemoveChannel(channel->GetName());
                std::cout << "Channel " << channel->GetName() << " is empty and removed." << std::endl;
            }
        }
    }

    // 2. Sunucuya, bu istemciyi ayırması talimatını ver
    // Bu, soketi kapatacak ve Client nesnesini silecek.
    _server.HandleClientDisconnection(sender->GetFD());

    std::cout << "Client " << sender->GetNickName() << " (" << sender->GetFD() << ") has quit with message: '" << quit_message << "'" << std::endl;
}
