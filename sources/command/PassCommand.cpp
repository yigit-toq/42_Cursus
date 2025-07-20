/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:30:38 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 16:37:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"

PassCommand::PassCommand(Server& server) : _server(server) {}

PassCommand::~PassCommand() {}

void PassCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered())
	{
		_server.SendsNumericReply(sender, 462, "You may not reregister"); // ERR_ALREADYREGISTRED
		return;
	}
	if (msg.GetParameters().empty())
	{
		_server.SendsNumericReply(sender, 461, "PASS :Not enough parameters"); // ERR_NEEDMOREPARAMS
		return;
	}

	std::string password = msg.GetParameters()[0];

	// Sunucu şifresini kontrol et
	if (password != _server.GetPassword())
	{
		_server.SendsNumericReply(sender, 464, "Password incorrect"); // ERR_PASSWDMISMATCH
		// Yanlış şifre durumunda bağlantıyı kapatmak iyi bir güvenlik pratiğidir.
		_server.HandleClientDisconnection(sender->GetFD());
		return;
	}

	sender->SetPassword(password); // Şifreyi kullanıcı nesnesine kaydet
	std::cout << "User FD " << sender->GetFD() << " provided correct password." << std::endl;

	// Şifre doğruysa kayıt kontrolünü tetikle
	_server.CheckRegistration(sender);
}