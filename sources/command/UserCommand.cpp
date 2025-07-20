/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:31 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 16:44:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"
#include "Server.hpp"

UserCommand:: UserCommand(Server& server) : _server(server) {}

UserCommand::~UserCommand() {}

void UserCommand::Execute(Client* sender, const Message& msg)
{
	if (sender->IsRegistered())
	{
		_server.SendsNumericReply(sender, 462, "You may not reregister"); // ERR_ALREADYREGISTRED
		return;
	}

	if (msg.GetParameters().size() < 4)
	{
		_server.SendsNumericReply(sender, 461, "USER :Not enough parameters"); // ERR_NEEDMOREPARAMS
		return;
	}

	std::string username = msg.GetParameters()[0];
	// Mod parametresi (msg.GetParameters()[1]) şimdilik kullanılmıyor, RFC'ye göre 0 veya 8 olmalı.
	// unused parametresi (msg.GetParameters()[2]) şimdilik kullanılmıyor.
	std::string realname = msg.GetParameters()[3]; // trailing parameter

	// Kullanıcı adının geçerliliğini kontrol et (örn: boş olamaz)
	if (username.empty() || realname.empty())
	{
		_server.SendsNumericReply(sender, 461, "USER :Invalid username or realname");
		return;
	}

	sender->SetUserName(username);
	sender->SetRealName(realname);

	if (sender->GetStatus() == UNREGISTERED || sender->GetStatus() == NICK_SET)
	{
		sender->SetStatus(USER_SET);
	}
	std::cout << "User FD " << sender->GetFD() << " username set to: " << username << ", realname: " << realname << std::endl;

	// Kayıt kontrolünü tetikle
	_server.CheckRegistration(sender);
}
