/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/06/24 17:48:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string>
#include "Socket.hpp"
#include "User.hpp"
#include "PollHandler.hpp"

#define BUFFER_SIZE	512

class Server
{
	private:
		Socket _server_socket;
		PollHandler _poll_handler;
		std::map<int, User*> _users;

		void HandleNewConnection();
		void HandleClientMessage(int client_fd);
		void HandleClientDisconnection(int fd);

	public:
		Server (int port);

		~Server();

		void Start();
};

#endif
