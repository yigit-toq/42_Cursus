/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:15:20 by ytop              #+#    #+#             */
/*   Updated: 2025/07/07 16:25:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

NickCommand:: NickCommand() {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Client* sender, const Message& msg)
{
	std::cout << "Executing NICK command for user FD " << sender->GetFD() << std::endl;

	if (msg.getParameters().empty())
	{
		std::cout << "NICK command requires a nickname. (Error: ERR_NONICKNAMEGIVEN)" << std::endl;

		return ;
	}

	std::string new_nick =	msg.	getParameters	()[0];

	std::cout << "User " << sender->GetNickName		() << " wants to change nick to: " << new_nick << std::endl;
}
