/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:43:36 by ytop              #+#    #+#             */
/*   Updated: 2025/06/20 15:47:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int port) : _fd(-1), _port(port)
{
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(port);
}

Socket::~Socket()
{
	if (_fd != -1)
	{
		close(_fd);
	}
}

void Socket::Create()
{
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)
	{
		throw std::runtime_error("Failed to create socket");
	}

	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_fd);
		throw std::runtime_error("Failed to set socket to non-blocking mode");
	}
}

void Socket::Bind()
{
	if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		close(_fd);
		throw std::runtime_error("Failed to bind socket");
	}
}

void Socket::Listen(int backlog)
{
	if (listen(_fd, backlog) < 0)
	{
		close(_fd);
		throw std::runtime_error("Failed to listen on socket");
	}
	std::cout << "Socket is listening on port " << _port << std::endl;
}

int Socket::Accept()
{
	socklen_t addrlen = sizeof(_address);

	int client_fd = accept(_fd, (struct sockaddr *)&_address, &addrlen);

	if (client_fd < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			throw std::runtime_error("Failed to accept connection");
		}
		return -1; // No pending connections
	}
	return client_fd;
}

int Socket::Receive(int fd, char *buffer, size_t length)
{
	memset(buffer, 0, length);

	ssize_t bytes_received = recv(fd, buffer, length, 0);

	if (bytes_received < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			throw std::runtime_error("Failed to receive data");
		}
		return -1; // No data available
	}
	return static_cast<int>(bytes_received);
}

int Socket::GetFd() const
{
	return _fd;
}

int Socket::GetPort() const
{
	return _port;
}
