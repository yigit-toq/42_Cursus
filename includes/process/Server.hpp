/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/06/27 15:31:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string>
#include "Socket.hpp"
#include "Client.hpp"
#include "PollHandler.hpp"
#include <cstdlib>

#define BUFFER_SIZE	512

class Server
{
	private:
		Socket					_srvr_socket;
		PollHandler				_poll_handlr;
		std::map<int, Client*>	_users;

		void HandleNewConnection		();
		void HandleClientMessage		(int fd);
		void HandleClientDisconnection	(int fd);

	public:
		Server		(int port, int pass);

		~Server		();

		void Start	();
};

#endif
