/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:09:44 by ytop              #+#    #+#             */
/*   Updated: 2025/07/24 23:48:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class ModeCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		ModeCommand				(const ModeCommand& other);
		ModeCommand& operator=	(const ModeCommand& other);

	public:
		 ModeCommand			(Server& server);
		~ModeCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
