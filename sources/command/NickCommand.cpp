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

void NickCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered())
	{
		// Kayıtlı bir kullanıcı nick değiştirmek isterse
		// Eski nick'i kontrol edip yeni nick'i ayarla
		// Diğer kullanıcılara bildirim gönder (JOIN/PART gibi)
		// Şimdilik sadece debug çıktısı
		std::cout << "User " << sender->GetNickName() << " trying to change nick to: " << msg.GetParameters()[0] << std::endl;
	} else {
		// Kayıtsız kullanıcı nick ayarlamak isterse
		std::cout << "Unregistered user FD " << sender->GetFD() << " attempting to set nick." << std::endl;
	}

	if (msg.GetParameters().empty()) {
		_server.SendsNumericReply(sender, 431, "No nickname given"); // ERR_NONICKNAMEGIVEN
		return;
	}

	std::string new_nick = msg.GetParameters()[0];

	// Nickname uzunluk kontrolü (RFC'ye göre 9 karakter)
	if (new_nick.length() > 9) {
		new_nick = new_nick.substr(0, 9); // Kırp
	}

	// Nickname'in geçerliliğini ve benzersizliğini kontrol et
	if (!_server.IsNicknameAvailable(new_nick) && new_nick != sender->GetNickName()) { // Kendi nick'i ise sorun yok
		_server.SendsNumericReply(sender, 433, new_nick + " :Nickname is already in use"); // ERR_NICKNAMEINUSE
		return;
	}

	// Nickname değişimi veya ayarlanması başarılı
	sender->SetNickName(new_nick);
	if (sender->GetStatus() == UNREGISTERED)
	{
		sender->SetStatus(NICK_SET);
	}
	std::cout << "User FD " << sender->GetFD() << " nickname set to: " << new_nick << std::endl;

	// Kayıt kontrolünü tetikle
	_server.CheckRegistration(sender);
}
