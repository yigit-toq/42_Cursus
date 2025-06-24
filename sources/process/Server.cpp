/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:26 by ytop              #+#    #+#             */
/*   Updated: 2025/06/24 17:48:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <vector>
#include <errno.h>

Server::Server(int port) : _server_socket(port), _poll_handler()
{
	_server_socket.Create();
	_server_socket.Bind();
	_server_socket.Listen(5);
	_poll_handler.AddSocket(_server_socket.GetFd(), POLLIN);
}

Server::~Server()
{
	for (auto &pair : _users)
	{
		delete pair.second;
	}
}

void Server::Start()
{
	while (true) {
        // Pollhandler'dan olayları bekle
        std::vector<struct pollfd> active_fds = _poll_handler.waitForEvents();

        for (size_t i = 0; i < active_fds.size(); ++i) {
            int fd = active_fds[i].fd;
            short revents = active_fds[i].revents;

            if (revents & POLLERR || revents & POLLNVAL) {
                // Hata durumu veya geçersiz dosya tanımlayıcı
                std::cerr << "Error or invalid FD: " << fd << std::endl;
                if (_users.count(fd)) { // Eğer bir kullanıcı ise
                    disconnectClient(fd);
                }
                _poll_handler.removeFd(fd);
                continue;
            }

            if (fd == _server_socket.getFd()) {
                // Sunucu soketinde bir olay varsa (yeni bağlantı)
                if (revents & POLLIN) {
                    handleNewConnection();
                }
            } else {
                // İstemci soketinde bir olay varsa
                if (revents & POLLIN) {
                    handleClientData(fd); // İstemciden veri oku
                }
                // Diğer olaylar (POLLOUT vb.) burada ele alınabilir
            }
        }
    }
}

void Server::handleNewConnection()
{
	int client_fd = _server_socket.Accept();
	if (client_fd < 0) {
		std::cerr << "Failed to accept new connection: " << strerror(errno) << std::endl;
		return;
	}

	User *new_user = new User(client_fd);
	_users[client_fd] = new_user;

	_poll_handler.AddSocket(client_fd, POLLIN);
	std::cout << "New connection accepted: FD " << client_fd << std::endl;
}

void	Server::HandleClientMessage(int client_fd)
{
	har buffer[BUFFER_SIZE + 1]; // +1 null sonlandırma için
    int bytes_read = _server_socket.receive(client_fd, buffer, BUFFER_SIZE);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null sonlandırma
        User* user = _users[client_fd];
        if (user) {
            user->appendToInputBuffer(buffer); // Gelen veriyi kullanıcının tamponuna ekle
            std::cout << "Received " << bytes_read << " bytes from FD " << client_fd << ": " << buffer << std::endl;

            // Tampondaki tam mesajları kontrol et ve işle
            std::string message;
            while ((message = user->extractNextMessage()) != "") {
                std::cout << "Full message extracted: " << message; // CRLF içerir
                // Burada Message sınıfını kullanarak 'message' stringini ayrıştırın
                // Sonra ilgili CommandHandler'a yönlendirin.
                // Örneğin: Message parsed_msg; parsed_msg.parse(message);
                // processMessage(user, parsed_msg);
            }
        }
    } else if (bytes_read == 0) {
        // İstemci bağlantıyı kapattı (EOF)
        std::cout << "Client FD " << client_fd << " disconnected." << std::endl;
        disconnectClient(client_fd);
    } else if (bytes_read == -1) {
        // Gerçek bir hata oluştu
        std::cerr << "Error reading from client FD " << client_fd << std::endl;
        disconnectClient(client_fd);
    }
}

void Server::HandleClientDisconnection(int fd)
{
	std::cout << "Client FD " << fd << " disconnected." << std::endl;
	_poll_handler.RemoveSocket(fd);
	delete _users[fd];
	_users.erase(fd);
}
