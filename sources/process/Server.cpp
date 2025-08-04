/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:26 by ytop              #+#    #+#             */
/*   Updated: 2025/08/04 22:49:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//bakılacak

Server:: Server(int port, std::string pass) : _srvr_socket(port), _password(pass)
{
	_srvr_socket.Create		();
	_srvr_socket.Binder		();
	_srvr_socket.Listen		();

	_poll_handlr.AddSocket	(_srvr_socket.GetSock(), POLLIN);

	SetupCommands			();

	_netwrk_name = "irc_network"	;
	_server_name = "irc.example.com";

	std::cout << "Server started on port " << port << std::endl;
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		delete (it->second);
	}
	_clients.clear();

	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		delete (it->second);
	}
	_channels.clear();

	for (std::map<std::string, CommandHandler*>::iterator it = _cmds_handlr.begin(); it != _cmds_handlr.end(); ++it)
	{
		delete (it->second);
	}
	_cmds_handlr.clear();

	std::cout << "Server shutting down." << std::endl;
}

void Server::Start()
{
	while (true)
	{
		std::vector<struct pollfd> active_fds = _poll_handlr.WaitForEvents(); // Olayları Bekle

		for (size_t i = 0; i < active_fds.size(); ++i) // Aktif Dosya Tanımlayıcılarını İşle
		{
			int	curr_fd = active_fds[i].fd;

			if (curr_fd == _srvr_socket.GetSock()) // Sunucu Soketi (Yeni Bağlantılar)
			{
				if (active_fds[i].revents & POLLIN)
					HandleNewConnection();
			}
			else // İstemci Soketleri
			{
				Client* user = _clients[curr_fd];

				if (!user)
				{
					std::cerr << "Error: User not found for FD " << curr_fd << std::endl;

					_poll_handlr.RmvSocket(curr_fd);

					continue ;
				}

				if (active_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) // Hata durumu kontrolü (bağlantı hatası veya kesilmesi)
				{
					std::cerr << "Client FD " << curr_fd << " error or hangup." << std::endl;

					ClientDisconnection(curr_fd);

					continue ;
				}

				if ( active_fds[i].revents & POLLIN) // Okuma Olayı
				{
					HandleClientMessage(curr_fd);
				}

				if ((active_fds[i].revents & POLLOUT) && user->HasOuputData()) // Yazma Olayı
				{
					while (user->HasOuputData()) // Kullanıcının output buffer'ındaki tüm veriyi göndermeye çalış
					{
						const std::string& data_to_send = user->GetOutputBuffer();

						int bytes_sent = _srvr_socket.Sender(user->GetFD(), (char *)data_to_send.c_str(), data_to_send.length());

						if (bytes_sent == -1)
						{
							if (errno == EAGAIN || errno == EWOULDBLOCK)
							{
								std::cout << "Send  buffer full for FD " << user->GetFD() << ", will try again next poll."	<< std::endl;

								break ;
							}
							else // Ciddi bir gönderme hatası (örneğin bağlantı koptu)
							{
								std::cerr << "Error sending data to FD " << user->GetFD() << ": " << strerror(errno)		<< std::endl;

								ClientDisconnection(user->GetFD());
								break ;
							}
						}
						else if (bytes_sent == 0)
						{
							std::cout << "Sent 0 bytes for FD " << user->GetFD() << ", likely no more data or unexpected behavior. Breaking send loop." << std::endl;

							break ;
						}
						else
						{
							user->PopOutputBuffer(bytes_sent);

							std::cout << "Sent " << bytes_sent << " bytes to FD " << user->GetFD() << ". Remaining in buffer: " << user->GetOutputBuffer().length() << " bytes." << std::endl;
						}
					}

					if (!user->HasOuputData())
					{
						_poll_handlr.SetEvents(user->GetFD(), POLLIN);

						std::cout << "FD " << user->GetFD() << " output buffer empty. POLLOUT removed." << std::endl;
					}
				}
				// if (user->HasOuputData() && !(_poll_handlr.GetEvents(user->GetFD()) & POLLOUT))
				// {
				// 	_poll_handlr.SetEvents(user->GetFD(), POLLIN | POLLOUT);
				//
				// 	std::cout << "FD " << user->GetFD() << " has new output data, setting POLLIN | POLLOUT." << std::endl;
				// }
			}
		}
	}
}

void	Server::HandleNewConnection()
{
	int client_fd = _srvr_socket.Accept();

	if (client_fd < 0)
	{
		std::cerr << "Failed to accept new connection: " << strerror(errno) << std::endl;
		return ;
	}

	Client* new_user = new Client(client_fd);
	new_user->SetHostName("irc.example.com");

	_clients[client_fd] = new_user;

	_poll_handlr.AddSocket(client_fd, POLLIN | POLLOUT);

	std::cout << "New connection accepted: FD " << client_fd << std::endl;
}

void	Server::HandleClientMessage(int client_fd)
{
	char	buffer[BUFFER_SIZE + 1];

	memset (buffer, 0, sizeof(buffer));

	int bytes_read = _srvr_socket.Receive(client_fd, buffer, BUFFER_SIZE);

	if (bytes_read > 0)
	{
		Client*	user = _clients[client_fd];

		if (user)
		{
			user->AppendToInputBuffer(buffer);

			std::cout << "Received " << bytes_read << " bytes from FD " << client_fd << ": [" << buffer << "]" << std::endl;

			std::string	raw;

			while ((raw = user->ExtractNextMessage()) != "")
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
		ClientDisconnection(client_fd);
	}
	else if (bytes_read == -1)
	{
		std::cerr << "Error reading from client FD " << client_fd << std::endl;

		ClientDisconnection(client_fd);
	}
}

void	Server::ClientDisconnection(int fd)
{
	Client* client_to_disconnect = _clients[fd];

	if (client_to_disconnect)
	{
		_poll_handlr.RmvSocket	(fd);
		_srvr_socket.RmvSock	(fd);
		
		delete (client_to_disconnect);

		_clients.erase(fd);

		std::cout << "Client FD " << fd << " disconnected and resources freed." << std::endl;
	}
}

void	Server::SetupCommands()
{
	_cmds_handlr["TOPIC"]	= new TopicCommand(*this);
	_cmds_handlr["NICK"]	= new NickCommand(*this);
	_cmds_handlr["USER"]	= new UserCommand(*this);
	_cmds_handlr["PASS"]	= new PassCommand(*this);
	_cmds_handlr["JOIN"]	= new JoinCommand(*this);
	_cmds_handlr["PART"]	= new PartCommand(*this);
	_cmds_handlr["MODE"]	= new ModeCommand(*this);
	_cmds_handlr["QUIT"]	= new QuitCommand(*this);
	
	_cmds_handlr["PRIVMSG"]	= new PrivCommand(*this);
}

void	Server::ProcessMessage(Client* sender, const Message& msg)
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

void	Server::CheckRegistration(Client* client)
{
	if (client->IsRegistered())
		return ;

	bool nick_set	= ( client->GetNickname() != "*");
	bool user_set	= (!client->GetUsername().empty() && !client->GetRealname().empty());

	bool pass_ok	= (_password.empty() || client->GetPassword() == _password);

	if (nick_set && user_set && pass_ok)
	{
		client->SetStatus(REGISTERED);

		std::cout << "User FD " << client->GetFD() << " (" << client->GetNickname() << ") is now registered!" << std::endl;

		SendsNumericReply(client, 001, "Welcome to the "	+ _netwrk_name + " IRC Network " + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname());

		SendsNumericReply(client, 002, "Your host is "		+ _server_name + ", running version 1.0");

		SendsNumericReply(client, 003, "This server was created 2025/07/20");
		SendsNumericReply(client, 004, _server_name			+ " 1.0 oiws O");
	}
}

void	Server::SendsNumericReply(Client* user, int numeric, const std::string& message) const // Genel numeric yanıt gönderme metodu
{
	std::stringstream ss;

	ss << ":" << _server_name << " " << std::setw(3) << std::setfill('0') << numeric << " " << user->GetNickname() << " :" << message << "\r\n";

	user->AppendToOuputBuffer(ss.str());
}

const std::string& Server::GetServerName() const { return _server_name; }
const std::string& Server::GetNetwrkName() const { return _netwrk_name; }

const std::string& Server::GetPassword	() const { return _password;	}

Client*	Server::FindUserByNickname(const std::string& nickname) const
{
	for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second->GetNickname() == nickname) 
		{
			return (it->second);
		}
	}
	return (NULL);
}

bool	Server::IsNicknameAvailable(const std::string& nickname) const
{
	if (nickname == "*") return (false);

	if (nickname.empty() || (!isalpha(nickname[0])	&&
		nickname[0] != '[' && nickname[0] != ']'	&&
		nickname[0] != '|' && nickname[0] != '`'	&&
		nickname[0] != '_' && nickname[0] != '^'	&&
		nickname[0] != '{' && nickname[0] != '}'	&& nickname[0] != '\\'))
	{
		return (false);
	}

	for (size_t i = 1; i < nickname.length(); ++i)
	{
		if (!isalnum(nickname[i]) &&
			nickname[i] != '[' && nickname[i] != ']' &&
			nickname[i] != '|' && nickname[i] != '`' &&
			nickname[i] != '_' && nickname[i] != '^' &&
			nickname[i] != '{' && nickname[i] != '}' && nickname[i] != '\\')
		{
			return (false);
		}
	}

	return (FindUserByNickname(nickname) == NULL);
}

Channel*	Server::FinderChannel(const std::string& name) const
{
	std::map<std::string, Channel*>::const_iterator it = _channels.find(name);

	if (it != _channels.end())
	{
		return (it->second);
	}

	return (NULL);
}

Channel*	Server::CreateChannel(const std::string& name)
{
	if (FinderChannel(name) != NULL)
	{
		std::cerr << "Attempted to create already existing channel: " << name << std::endl;

		return (FinderChannel(name));
	}

	Channel* new_channel	= new Channel(name, *this);

	_channels[name]			= new_channel;

	std::cout << "Created new channel: " << name << std::endl;

	return (new_channel);
}

void		Server::RemoveChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);

	if (it != _channels.end())
	{
		delete (it->second);

		_channels.erase(it);

		std::cout << "Removed empty channel: " << name << std::endl;
	}
}

PollHandler& Server::GetPollHandler()
{
	return (_poll_handlr);
}

Client* Server::FindClient(const std::string& nick) //
{
	std::map<std::string, Client*>::iterator it = _clients_by_nick.find(nick);

	if (it != _clients_by_nick.end())
	{
		return it->second;
	}
	return NULL; // Client bulunamadı
}

void Server::BroadcastChannelMessage(Channel* channel, Client* sender, const std::string& message)
{
	if (!channel)
		return ;

	const std::map<int, Client*>& users = channel->getUsers();

	std::map<int, Client*>::const_iterator it;
	
	std::string full_message = ":" + sender->GetNickname() + " " + message + "\r\n";

	for (it = users.begin(); it != users.end(); ++it)
	{
		// Mesajı gönderen kullanıcı hariç herkese gönder
		if (it->second->GetFD() != sender->GetFD())
		{
			std::cout << "Broadcasting message to " << it->second->GetNickname() << ": " << full_message;
			if (send(it->second->GetFD(), full_message.c_str(), full_message.length(), 0) < 0)
			{
				// Hata yönetimi burada yapılabilir
			}
		}
	}
}

