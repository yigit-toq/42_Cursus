/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:26 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:57:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string pass) : _password(pass), _srvr_socket(port)
{
	_srvr_socket.Create		();
	_srvr_socket.Binder		();
	_srvr_socket.Listen		();

	_poll_handlr.AddSocket	(_srvr_socket.GetSock(), POLLIN);

	SetupCommandHandlers	();

	_server_name = "irc.example.com"; //
	_network_name = "irc_network"; //

	std::cout << "Server started on port " << port << std::endl;
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator					it = _users			.begin()	; it != _users.end()		; ++it)
	{
		delete (it->second);
	}
	_users.clear();

	for (std::map<std::string, CommandHandler*>::iterator	it = _cmds_handlr	.begin()	; it != _cmds_handlr.end()	; ++it)
	{
		delete (it->second);
	}
	_cmds_handlr.clear();

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
			int		curr_fd	= active_fds[i].fd;

			if (curr_fd == _srvr_socket.GetSock())
			{
				if (active_fds[i].revents & POLLIN)
					HandleNewConnection();
			}
			else
			{
				// Mevcut istemciden veri
				Client* user = _users[curr_fd];
				if (user) {
					if (active_fds[i].revents & POLLIN)
					{
						HandleClientMessage(curr_fd);
					}
					if (active_fds[i].revents & POLLOUT && user->HasOuputData())
					{
						// Eğer istemcinin çıkış tamponunda gönderilecek veri varsa
						// Bu kısımda sokete yazma işlemini gerçekleştireceğiz.
						std::string msg_to_send = user->NextOutputMessage();
						int bytes_sent = _srvr_socket.Send(user->GetFD(), (char*)msg_to_send.c_str(), msg_to_send.length());
						if (bytes_sent == -1)
						{
							std::cerr << "Error sending data to FD " << user->GetFD() << std::endl;
							HandleClientDisconnection(user->GetFD());
						}
						else
						{
							std::cout << "Sent " << bytes_sent << " bytes to FD " << user->GetFD() << ": [" << msg_to_send << "]" << std::endl;

							// Eğer tamponda hala mesaj varsa POLLOUT'u açık tut
							if (user->HasOuputData())
							{
								_poll_handlr.SetEvents(user->GetFD(), POLLIN | POLLOUT);
							}
							else
							{
								// Tampon boşaldıysa sadece POLLIN'e dön
								_poll_handlr.SetEvents(user->GetFD(), POLLIN);
							}
						}
					}

					if (user->HasOuputData() && !(active_fds[i].revents & POLLOUT))
					{
						_poll_handlr.SetEvents(user->GetFD(), POLLIN | POLLOUT);
					}
				}
			}
		}
	}
}

void Server::HandleNewConnection() //
{
	int client_fd = _srvr_socket.Accept();

	if (client_fd < 0)
	{
		std::cerr << "Failed to accept new connection: " << strerror(errno) << std::endl;
		return ;
	}

	Client* new_user = new Client(client_fd);
	new_user->SetHostName("irc.example.com");
	_users[client_fd] = new_user;
	_poll_handlr.AddSocket(client_fd, POLLIN | POLLOUT);

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

			std::string	raw;

			while ((raw = user->ExtrctNextMessage()) != "")
			{
				std::cout << "Full message extracted: " << raw << std::endl;

				Message	msg;

				if (msg.Parse(raw))
				{
					msg.Print();

					ProcessMessage(user, msg);
				}
				else
				{
					std::cerr << "Failed to parse message from FD " << client_fd << ": " << raw << std::endl;

					// Geçersiz mesaj durumunda istemciye hata yanıtı gönderme veya bağlantıyı kesme düşünülebilir.
				}
			}
		}
	}
	else if (bytes_read ==  0)
	{
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
	std::cout << "Client FD"  << fd << " disconnected." << std::endl;

	_poll_handlr.RmvSocket(fd);

	delete (_users[fd]);

	_users.erase(fd);
}

void	Server::SetupCommandHandlers()
{
	_cmds_handlr["NICK"] = new NickCommand(*this); // this bir IRCServer* olduğu için *this ile referansını al
	_cmds_handlr["USER"] = new UserCommand(*this);
	_cmds_handlr["PASS"] = new PassCommand(*this); // PassCommand'ı da ekle
}

void	Server::ProcessMessage(Client* sender, const Message& msg) //
{
	std::map<std::string, CommandHandler*>::iterator it = _cmds_handlr.find(msg.GetCommand());

	if (it != _cmds_handlr.end())
	{
		it->second->Execute(sender, msg);
	}
	else
	{
		std::cerr << "Unknown command: " << msg.GetCommand() << " from FD " << sender->GetFD() << std::endl;
	}
}

void	Server::CheckRegistration(Client* client) //
{
	if (client->IsRegistered())
	{
		return ;
	}

	bool nick_set = (client->GetNickName() != "*"); // Varsayılan nick değişmişse
	bool user_set = (!client->GetUserName().empty() && !client->GetRealName().empty());
	bool password_ok = (_password.empty() || client->GetPassword() == _password); // Sunucu şifresi yoksa veya doğruysa

	if (nick_set && user_set && password_ok) {
		client->SetStatus(REGISTERED);
		std::cout << "User FD " << client->GetFD() << " (" << client->GetNickName() << ") is now registered!" << std::endl;

		SendsNumericReply(client, 001, "Welcome to the " + _network_name + " IRC Network " + client->GetNickName() + "!" + client->GetUserName() + "@" + client->GetHostName());
		SendsNumericReply(client, 002, "Your host is " + _server_name + ", running version 1.0");
		SendsNumericReply(client, 003, "This server was created 2024/01/01"); // Oluşturulma tarihi
		SendsNumericReply(client, 004, _server_name + " 1.0 oiws O"); // Server adı, versiyon, kullanıcı modları, kanal modları
	}
}

// Yeni: Genel numeric yanıt gönderme metodu
void	Server::SendsNumericReply(Client* user, int numeric, const std::string& message) const
{
	std::stringstream ss;
	ss << ":" << _server_name << " " << std::setw(3) << std::setfill('0') << numeric
	<< " " << user->GetNickName() << " :" << message << "\r\n";
	user->AppendToOuputBuffer(ss.str());

	// std::cout << "Sending reply to " << user->GetNickName() << ": " << ss.str() << std::endl; // Debug
}

// Yeni Getter'lar
const std::string& Server::GetServerName() const { return _server_name; }
const std::string& Server::GetNetworkName() const { return _network_name; }
const std::string& Server::GetPassword() const { return _password; }

// Yeni: Kullanıcı nickname'i ile bulma
Client*	Server::FindUserByNickname(const std::string& nickname) const
{
	for (std::map<int, Client*>::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->second->GetNickName() == nickname) 
		{
			return (it->second);
		}
	}
	return NULL;
}

// Yeni: Nickname kullanılabilir mi kontrolü
bool	Server::IsNicknameAvailable(const std::string& nickname) const
{
	// Geçici nickname'in ("*") özel durumu
	if (nickname == "*") return false;

	// Geçersiz karakterler kontrolü (RFC 2812, Bölüm 2.3.1)
	// nick = letter { letter | digit | special }
	// special = %x5B-60 / %x7B-7D ; "[", "]", "\", "`", "_", "^", "{", "|", "}"
	// İlk karakter digit olamaz.
	if (nickname.empty() || (!isalpha(nickname[0]) && nickname[0] != '[' && nickname[0] != ']' && nickname[0] != '\\' && nickname[0] != '`' && nickname[0] != '_' && nickname[0] != '^' && nickname[0] != '{' && nickname[0] != '|' && nickname[0] != '}')) {
		return false; // Geçersiz ilk karakter
	}
	for (size_t i = 1; i < nickname.length(); ++i) {
		if (!isalnum(nickname[i]) && nickname[i] != '[' && nickname[i] != ']' && nickname[i] != '\\' && nickname[i] != '`' && nickname[i] != '_' && nickname[i] != '^' && nickname[i] != '{' && nickname[i] != '|' && nickname[i] != '}') {
			return false; // Geçersiz karakter
		}
	}

	return FindUserByNickname(nickname) == NULL; // Nickname kullanılıyor mu
}
