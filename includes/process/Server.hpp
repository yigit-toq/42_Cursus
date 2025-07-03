/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 19:33:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#pragma region header

#include <map>
#include <cstdlib>

#include "Socket.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "PollHandler.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "CommandHandler.hpp"

#pragma endregion

#define BUFFER_SIZE	512

class Server
{
	private:
		std::map<std::string, CommandHandler*>	_cmds_handlr;
		PollHandler								_poll_handlr;

		Socket									_srvr_socket;

		std::map<int, Client*>					_users;

		void HandleNewConnection		();
		void HandleClientMessage		(int fd);
		void HandleClientDisconnection	(int fd);

		Server							(const Server&);
    	Server& operator=				(const Server&);

		void	SetupCommandHandlers	();
		void	ProcessMessage			(Client* sender, const Message& msg);

	public:
		 Server		(int port, int pass);

		~Server		();

		void Start	();
};

#endif
