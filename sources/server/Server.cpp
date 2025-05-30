/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:23:27 by ytop              #+#    #+#             */
/*   Updated: 2025/05/30 17:23:29 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, const std::string &host) : _port(port), _host(host)
{
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ErrorHandler("Failed to create socket");
	}

	sockaddr_in	serverAddress = *GetServerAddress();

	if (bind  (_socket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		close (_socket);

		ErrorHandler("Failed to bind socket");
	}

	if (listen(_socket, SOMAXCONN) < 0)
	{
		close (_socket);

		ErrorHandler("Failed to list socket");
	}

	std::cout << "Server started on " << _host << ":" << _port << std::endl;
}

void	Server::Start()
{
	while (true)
	{
	}
}

sockaddr_in*	Server::GetServerAddress()
{
	static sockaddr_in	serverAddress;

	serverAddress.sin_port			= htons(_port);

	serverAddress.sin_family		= AF_INET;
	serverAddress.sin_addr.s_addr	= INADDR_ANY;

	return (&serverAddress);
}

#pragma region Utility Functions

void	ErrorHandler(const std::string &message)
{
	std::cerr << "Error: " << message << std::endl;

	exit(EXIT_FAILURE);
}

#pragma endregion
