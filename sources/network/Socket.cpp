/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:30:20 by ytop              #+#    #+#             */
/*   Updated: 2025/06/30 16:36:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket:: Socket(int port) : _port(port), _sock(-1)
{
	_address.sin_port			= htons(port)	;

	_address.sin_family			= AF_INET		;

	_address.sin_addr.s_addr	= INADDR_ANY	;
}

Socket::~Socket()
{
	if (_sock != -1)
	{
		close(_sock);
	}
}

void Socket::Listen	(int backlog)
{
	if (listen(_sock, backlog) < 0)
	{
		close (_sock);

		throw std::runtime_error("Failed to listen on socket");
	}

	std::cout << "Socket is listening on port " << _port << std::endl;
}

void Socket::Create	(void)
{
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (_sock < 0)
	{
		throw std::runtime_error("Failed to create socket");
	}

	if (fcntl(_sock, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_sock);

		throw std::runtime_error("Failed to set socket to non-blocking mode");
	}
}

void Socket::Bind	(void)
{
	if (bind(_sock, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		close(_sock);

		throw std::runtime_error("Failed to bind socket");
	}
}

int	Socket::Send	(int fd, char *buffer, size_t length)
{
	(void)buffer;
	(void)length;
	(void)fd;

	return (0);
}

int	Socket::Receive(int fd, char *buffer, size_t length)
{
	memset(buffer, 0, length);

	ssize_t	bytes_received = recv(fd, buffer, length, 0);

	if (bytes_received < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			throw std::runtime_error("Failed to receive data");
		}
		return (-1);
	}
	return (static_cast<int>(bytes_received));
}

int	Socket::GetSock	() const
{
	return (_sock);
}

int	Socket::GetPort	() const
{
	return (_port);
}

int	Socket::Accept	()
{
	socklen_t	addrlen = sizeof(_address);

	int	client_fd = accept(_sock, (struct sockaddr *)&_address, &addrlen);

	if (client_fd < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			throw std::runtime_error("Failed to accept connection");
		}
		return (-1);
	}
	return (client_fd);
}
