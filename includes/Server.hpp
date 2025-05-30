/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:23:35 by ytop              #+#    #+#             */
/*   Updated: 2025/05/30 17:37:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#pragma region Includes

#include <iostream>

#include <stdlib.h>
#include <unistd.h>

#include <sys/poll.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <vector>
#include <map>

#pragma endregion

void	ErrorHandler(const std::string &message);

class Server
{
	private:
		int	_port;
		int	_socket;

		std::string	_host;

		std::vector<pollfd>			_poolFDs;
		std::map<int, std::string>	_clients;

	public:
		Server(int port, const std::string &host);

		sockaddr_in*	GetServerAddress();

		void			Start();
};

#endif
