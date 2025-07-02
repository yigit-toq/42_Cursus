/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:26 by ytop              #+#    #+#             */
/*   Updated: 2025/07/02 18:13:27 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, int pass) : _srvr_socket(port)
{
	(void)pass;

	_srvr_socket.Create		();
	_srvr_socket.Bind		();

	_srvr_socket.Listen		();

	_poll_handlr.AddSocket	(_srvr_socket.GetSock(), POLLIN);

	std::cout << "Server started on port " << port << std::endl;
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		delete (it->second);
	}
	_users.clear();

	_poll_handlr.RmvSocket(_srvr_socket.GetSock());

	std::cout << "Server shutting down." << std::endl;
}

void Server::Start()
{
	while (true)
	{
		std::vector<struct pollfd> active_fds = _poll_handlr.WaitForEvents();

		for (size_t i = 0; i < active_fds.size(); ++i)
		{
			int		fd		= active_fds[i].fd;

			short	revents	= active_fds[i].revents;

			if (revents & POLLERR || revents & POLLNVAL)
			{
				std::cerr << "Error or invalid FD: " << fd << std::endl;

				if (_users.count(fd))
					HandleClientDisconnection(fd);

				_poll_handlr.RmvSocket(fd);
				continue ;
			}

			if (fd == _srvr_socket.GetSock())
			{
				if (revents & POLLIN)
				{
					HandleNewConnection();
				}
			}
			else
			{
				if (revents & POLLIN)
				{
					HandleClientMessage(fd);
				}
				// Diğer olaylar (POLLOUT vb.) burada ele alınabilir
			}
		}
	}
}

void Server::HandleNewConnection()
{
	int client_fd = _srvr_socket.Accept();

	if (client_fd < 0)
	{
		std::cerr << "Failed to accept new connection: " << strerror(errno) << std::endl;
		return ;
	}

	Client *new_user	= new Client(client_fd);

	_users[client_fd]	= new_user;

	_poll_handlr.AddSocket(client_fd, POLLIN);

	std::cout << "New connection accepted: FD " << client_fd << std::endl;
}

void	Server::HandleClientMessage(int client_fd)
{
	char	buffer[BUFFER_SIZE + 1];

	memset(	buffer, 0, sizeof(buffer));

	int		bytes_read = _srvr_socket.Receive(client_fd, buffer, BUFFER_SIZE);

	if (bytes_read > 0)
	{
		Client*	user = _users[client_fd];

		if (user)
		{
			user->AppendToInputBuffer(buffer);

			std::cout << "Received " << bytes_read << " bytes from FD " << client_fd << ": [" << buffer << "]" << std::endl;

			std::string	message;

			while ((message = user->ExtractNextMessage()) != "")
			{
				std::cout << "Full message extracted: " << message << std::endl;

				Message	msg;
				if (msg.parse(message))
				{
					msg.print();

					// Şimdi 'msg' nesnesini kullanarak ilgili komut işleyicisine yönlendirebiliriz.
					// Örneğin: processMessage(user, msg);
				}
				else
				{
					std::cerr << "Failed to parse message from FD " << client_fd << ": " << message << std::endl;

					// Geçersiz mesaj durumunda istemciye hata yanıtı gönderme veya bağlantıyı kesme düşünülebilir.
				}
			}
		}
	}
	else if (bytes_read ==  0)
	{
		std::cout << "Client FD" << client_fd << " disconnected." << std::endl;

		HandleClientDisconnection(client_fd);
	}
	else if (bytes_read == -1)
	{
		std::cerr << "Error reading from client FD " << client_fd << std::endl;

		HandleClientDisconnection(client_fd);
	}
}

void	Server::HandleClientDisconnection(int fd)
{
	std::cout << "Client FD " << fd << " disconnected." << std::endl;

	_poll_handlr.RmvSocket(fd);

	delete (_users[fd]);

	_users.erase(fd);
}
