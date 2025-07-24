/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:47:57 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:14:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class QuitCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		QuitCommand				(const QuitCommand& other);
		QuitCommand& operator=	(const QuitCommand& other);

	public:
		 QuitCommand			(Server& server);
		~QuitCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
