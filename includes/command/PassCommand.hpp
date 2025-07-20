/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:29:05 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:34:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "CommandHandler.hpp"

#include "Server.hpp"
#include "Client.hpp"

class PassCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		PassCommand				(const PassCommand& other);
		PassCommand& operator=	(const PassCommand& other);

	public:
		 PassCommand			(Server& server);
		~PassCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
