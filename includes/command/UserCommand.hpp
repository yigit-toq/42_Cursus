/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:21 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:35:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class UserCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		UserCommand				(const UserCommand& other);
		UserCommand& operator=	(const UserCommand& other);

	public:
		 UserCommand			(Server& server);
		~UserCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
