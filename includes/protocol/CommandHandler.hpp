/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:58:33 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 18:14:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "Message.hpp"
#include "Client.hpp"

class Client;

class CommandHandler
{
	private:
		CommandHandler				(const CommandHandler& other);
		CommandHandler& operator=	(const CommandHandler& other);

	public:
				 CommandHandler();
		virtual ~CommandHandler();

		virtual void	execute(Client* sender, const Message& msg) = 0;
};

#endif
