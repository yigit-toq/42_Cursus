/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:16:28 by ytop              #+#    #+#             */
/*   Updated: 2025/07/21 17:18:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

# include "CommandHandler.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class Server;

class JoinCommand : public CommandHandler
{
	private:
		Server& 				_server;

	private:
		JoinCommand				(const JoinCommand& other);
		JoinCommand& operator=	(const JoinCommand& other);

	public:
		 JoinCommand			(Server& server);
		~JoinCommand			();

		void Execute			(Client* sender, const Message& msg);
};

#endif
