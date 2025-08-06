/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:47:55 by ytop              #+#    #+#             */
/*   Updated: 2025/08/06 23:41:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#pragma region header

#include <netinet/in.h>

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>

#pragma endregion

typedef struct sockaddr_in sockaddr_in;

class Socket
{
	private:
		int				_port;
		int				_sock;

		sockaddr_in		_addr;

	public:
		 Socket			(int port);
		~Socket			();

		int		Accept	(void);

		void	Listen	(int backlog = 5);
		void	Create	(void);
		void	Binder	(void);

		int 	Sender	(int fd, char *buffer, size_t length);

		int 	Receive	(int fd, char *buffer, size_t length);

		int 	GetSock	(void) const;
		int 	GetPort	(void) const;

		void 	RmvSock	(int fd);
};

#endif
