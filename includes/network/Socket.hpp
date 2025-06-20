/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:47:55 by ytop              #+#    #+#             */
/*   Updated: 2025/06/20 14:54:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>

#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <fcntl.h>

class Socket
{
	private:
		int	_fd;
		int	_port;

		struct sockaddr_in	_address;

	public:
		Socket (int port);

		~Socket();

		void	Create();
		void	Bind();
		void	Listen(int backlog = 5);
		int		Accept();

		int 	Receive(int fd, char *buffer, size_t length);

		int 	Send(int fd, const char *buffer, size_t length);

		int 	GetFd() const;
		int 	GetPort() const;
};

#endif
