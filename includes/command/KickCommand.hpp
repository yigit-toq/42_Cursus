/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 03:28:46 by ytop              #+#    #+#             */
/*   Updated: 2025/07/26 03:29:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class KickCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		KickCommand				(const KickCommand& other);
		KickCommand& operator=	(const KickCommand& other);

	public:
		 KickCommand			(Server& server);
		~KickCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
