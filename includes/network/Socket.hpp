/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:47:55 by ytop              #+#    #+#             */
/*   Updated: 2025/06/27 17:18:45 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#pragma region header

#include <netinet/in.h>

#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <cstring>
#include <cerrno>

#pragma endregion

typedef struct sockaddr_in sockaddr_in;

class Socket
{
	private:
		int					_port;
		int					_socket;

		sockaddr_in			_address;

	public:
		 Socket			(int port);

		~Socket			();

		int		Accept	();

		void	Listen	(int backlog = 5);
		void	Create	();
		void	Bind	();

		int 	Send	(int fd, char *buffer, size_t length);

		int 	Receive	(int fd, char *buffer, size_t length);

		int 	GetSock	() const;
		int 	GetPort	() const;
};

#endif
