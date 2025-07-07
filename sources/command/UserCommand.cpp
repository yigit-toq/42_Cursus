/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:31 by ytop              #+#    #+#             */
/*   Updated: 2025/07/07 16:25:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"

UserCommand:: UserCommand() {}

UserCommand::~UserCommand() {}

void UserCommand::execute(Client* sender, const Message& msg)
{
	std::cout << "Executing USER command for user FD " << sender->GetFD() << std::endl;

	if (msg.getParameters().size() < 4)
	{
		std::cout << "USER command requires 4 parameters: <username> <mode> <unused> :<realname> (Error: ERR_NEEDMOREPARAMS)" << std::endl;

		return ;
	}

	std::string username = msg.getParameters	()[0];

	// int mode = std::atoi(msg.getParameters	()[1].c_str());
	// std::string unused = msg.getParameters	()[2];

	std::string realname = msg.getParameters	()[3];

	std::cout << "User " << sender->GetNickName	() << " wants to set username: " << username << ", realname: " << realname << std::endl;

	// sender->setUsername(username);
	// sender->setRealname(realname);
}
