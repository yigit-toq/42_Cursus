/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:30:20 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 22:33:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket:: Socket(int port) : _port(port), _sock(-1)
{
	_addr.sin_port			= htons(port)	;

	_addr.sin_family			= AF_INET		;

	_addr.sin_addr.s_addr	= INADDR_ANY	;
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

	int optval = 1;

	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		close(_sock);

		throw std::runtime_error("Failed to set socket options");
	}

	if (fcntl(_sock, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_sock);

		throw std::runtime_error("Failed to set socket to non-blocking mode");
	}
}

void Socket::Binder	(void)
{
	if (bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		close(_sock);

		throw std::runtime_error("Failed to bind socket");
	}
}

int	Socket::Send	(int fd, char *buffer, size_t length)
{
	// Make sure the buffer isn't null and length is positive, though send() handles this.
	if (!buffer || length == 0)
	{
		return 0; // Nothing to send or invalid buffer
	}

	// Use the send() system call
	ssize_t bytes_sent = send(fd, buffer, length, 0); // Last param is flags, usually 0

	if (bytes_sent == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			// This means the socket's send buffer is full,
			// and we're in non-blocking mode.
			// We'll try again later when POLLOUT indicates it's ready.
			return 0; // Indicate no bytes were sent *this time* due to buffer full
		}
		// A real error occurred (e.g., connection reset by peer)
		std::cerr << "Error sending data to FD " << fd << ": " << strerror(errno) << std::endl;
		return -1; // Indicate a critical error
	}

	return static_cast<int>(bytes_sent);
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
	socklen_t	addrlen = sizeof(_addr);

	int	client_fd = accept(_sock, (struct sockaddr *)&_addr, &addrlen);

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
