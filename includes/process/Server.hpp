/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/06/30 16:09:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#pragma region header

#include <map>
#include <cstdlib>

#include "Socket.hpp"
#include "Client.hpp"
#include "PollHandler.hpp"

#pragma endregion

#define BUFFER_SIZE	512

class Server
{
	private:
		Socket							_srvr_socket;
		PollHandler						_poll_handlr;

		std::map<int, Client*>			_users;

		void HandleNewConnection		();
		void HandleClientMessage		(int fd);
		void HandleClientDisconnection	(int fd);

	public:
		 Server		(int port, int pass);

		~Server		();

		void Start	();
};

#endif
