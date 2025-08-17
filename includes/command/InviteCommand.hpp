/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:06:50 by ytop              #+#    #+#             */
/*   Updated: 2025/08/17 23:06:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class InviteCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		InviteCommand				(const InviteCommand& other);
		InviteCommand& operator=	(const InviteCommand& other);

	public:
		 InviteCommand				(Server& server);
		~InviteCommand				();

		void Execute				(Client* sender, const Message& msg);
};

#endif
