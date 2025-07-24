/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:46:22 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:13:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class PartCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		PartCommand				(const PartCommand& other);
		PartCommand& operator=	(const PartCommand& other);

	public:
		 PartCommand			(Server& server);
		~PartCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
