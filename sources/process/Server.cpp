/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:26 by ytop              #+#    #+#             */
/*   Updated: 2025/08/11 12:43:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server:: Server(int port, std::string pass) : _srvr_socket(port), _password(pass)
{
	_srvr_socket.Create		();
	_srvr_socket.Binder		();
	_srvr_socket.Listen		();

	_poll_handlr.AddSocket	(_srvr_socket.GetSock(), POLLIN);

	SetupCommands			();

	_netwrk_name = "irc_network"	;
	_server_name = "irc.example.com";

	Logger::getInstance().Log(INFO, "Server initialized on port " + ft_to_string(port) + " with password: " + pass);
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator					it = _clients.		begin(); it != _clients.	end(); ++it)
	{
		delete (it->second);
	}
	_clients.		clear();

	for (std::map<std::string, Channel*>::iterator			it = _channels.		begin(); it != _channels.	end(); ++it)
	{
		delete (it->second);
	}
	_channels.		clear();

	for (std::map<std::string, CommandHandler*>::iterator	it = _cmds_handlr.	begin(); it != _cmds_handlr.end(); ++it)
	{
		delete (it->second);
	}
	_cmds_handlr.	clear();

	Logger::getInstance().Log(INFO, "Server shutting down.");
}

//-------------------- Server Main Loop --------------------

void	Server::Start()
{
	while (true)
	{
		std::vector<struct pollfd> active_fds = _poll_handlr.WaitForEvents(1000);

		HandleEvents(active_fds);

		CheckForTimeouts(); //

		cleanupClients();
		cleanupChannels();
	}
}

void	Server::HandleEvents(const std::vector<struct pollfd>& active_fds)
{
	for (size_t i = 0; i < active_fds.size(); ++i)
	{
		int curr_fd = active_fds[i].fd;

		if (curr_fd == _srvr_socket.GetSock())
		{
			HandleServerSocketEvent(active_fds[i]);
		}
		else
		{
			HandleClientSocketEvent(active_fds[i]);
		}
	}
}

void	Server::HandleServerSocketEvent(const struct pollfd& server_fd)
{
	if (server_fd.revents & POLLIN)
	{
		HandleNewConnection();
	}
}

void	Server::HandleClientSocketEvent(const struct pollfd& client_fd)
{
	int		fd		= client_fd.fd;

	Client*	user	= _clients[fd];

	if (!user)
	{
		Logger::getInstance().Log(ERROR, "User not found for FD " + ft_to_string(fd));

		_poll_handlr.RmvSocket	(fd);

		return ;
	}

	if (client_fd.revents & (POLLERR | POLLHUP | POLLNVAL))
	{
		Logger::getInstance().Log(ERROR, "Client FD " + ft_to_string(fd) + " error or hangup.");

		ClientDisconnection		(fd);

		return ;
	}

	if ( client_fd.revents & POLLIN )
	{
		HandleClientReadEvent	(fd, user);
	}

	if ((client_fd.revents & POLLOUT) && user->HasOuputData())
	{
		HandleClientWriteEvent	(fd, user);
	}
}

void	Server::HandleClientReadEvent(int client_fd, Client* user)
{
	HandleClientMessage(client_fd);

	(void)user;
}

void	Server::HandleClientWriteEvent(int client_fd, Client* user)
{
	while (user->HasOuputData())
	{
		const std::string& data_to_send = user->GetOutputBuffer();

		int bytes_sent = _srvr_socket.Sender(user->GetFD(), (char *)data_to_send.c_str(), data_to_send.length());

		if (bytes_sent <= 0)
		{
			if (bytes_sent == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
			{
				Logger::getInstance().Log(WARNING, "Send buffer full for FD " + ft_to_string(user->GetFD()) + ", will try again next poll.");
			}
			else
			{
				Logger::getInstance().Log(ERROR, "Error sending data to FD " + ft_to_string(user->GetFD()) + ": " + strerror(errno));

				ClientDisconnection(user->GetFD());
			}
			break ;
		}
	
		user->PopOutputBuffer	(bytes_sent);

		Logger::getInstance().Log(INFO, "Sent " + ft_to_string(bytes_sent) + " bytes to FD " + ft_to_string(user->GetFD()) + ". Remaining: " + ft_to_string(user->GetOutputBuffer().length()) + " bytes.");
	}

	if (!user->HasOuputData())
	{
		_poll_handlr.SetEvents(user->GetFD(), POLLIN);

		Logger::getInstance().Log(INFO, "FD " + ft_to_string(user->GetFD()) + " output buffer empty. POLLOUT removed.");
	}

	(void)client_fd;
}

void	Server::HandleNewConnection()
{
	int client_fd = _srvr_socket.Accept();

	if (client_fd < 0)
	{
		Logger::getInstance().Log(ERROR, "Failed to accept new connection: " + std::string(strerror(errno)));
		return ;
	}

	Client* new_user = new Client(client_fd);
	new_user->SetHostname("irc.example.com");

	_clients[client_fd] = new_user;

	_poll_handlr.AddSocket(client_fd, POLLIN | POLLOUT);

	Logger::getInstance().Log(INFO, "New connection accepted: FD " + ft_to_string(client_fd));
}

void	Server::HandleClientMessage(int fd)
{
	char	buffer[BUFFER_SIZE + 1];

	memset (buffer, 0, sizeof(buffer));

	int bytes_read = _srvr_socket.Receive(fd, buffer, BUFFER_SIZE);

	if (bytes_read > 0)
	{
		Client*	user = _clients[fd];

		if (user)
		{
			user->AppendToInputBuffer(buffer);

			Logger::getInstance().Log(INFO, "Received " + ft_to_string(bytes_read) + " bytes from FD " + ft_to_string(fd) + ": [" + buffer + "]");

			std::string	raw;

			while ((raw = user->ExtractNextMessage()) != "")
			{
				Logger::getInstance().Log(INFO, "Full message extracted: " + raw);

				Message	msg;

				if (msg.Parse(raw))
				{
					msg.Print();

					ProcessMessage(user, msg);
				}
				else
				{
					Logger::getInstance().Log(ERROR, "Failed to parse message from FD " + ft_to_string(fd) + ": " + raw);

					// Geçersiz mesaj durumunda istemciye hata yanıtı gönderme veya bağlantıyı kesme düşünülebilir.
				}
			}
		}
	}
	else if (bytes_read ==  0)
	{
		ClientDisconnection(fd);
	}
	else if (bytes_read == -1)
	{
		Logger::getInstance().Log(ERROR, "Error reading from client FD " + ft_to_string(fd) + ": " + strerror(errno));

		ClientDisconnection(fd);
	}
}

void	Server::ClientDisconnection(int fd)
{
	std::map<int, Client*>::iterator it = _clients.find(fd);

	if (it == _clients.end())
	{
		return;
	}
	
	Client* client_ptr = it->second;

	std::vector<Channel *> joined_channels = client_ptr->GetJoinChannels(); 

	for (size_t i = 0; i < joined_channels.size(); ++i)
	{
		Channel *channel_ptr = joined_channels[i];
		
		if (channel_ptr)
		{
			channel_ptr->RmvClient(client_ptr);
		}
	}

	_fdsToDelete.push_back(fd);

	Logger::getInstance().Log(INFO, "Client FD " + ft_to_string(fd) + " disconnected. Removing from server.");
}

//------------------------------------------------------------

//-------------------- Channel Management --------------------

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
		Logger::getInstance().Log(WARNING, "Attempted to create already existing channel: " + name);

		return (FinderChannel(name));
	}

	Channel* new_channel	= new Channel(name, *this);

	_channels[name]			= new_channel;

	Logger::getInstance().Log(INFO, "Created new channel: " + name);

	return (new_channel);
}

void	Server::RemoveChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);

	if (it == _channels.end())
	{
		return;
	}

	_channelsToDelete.push_back(name);

	Logger::getInstance().Log(INFO, "Channel " + name + " marked for deletion.");
}

//------------------------------------------------------------

//-------------------- Client  Management --------------------

Client*	Server::FindClient	(const std::string& nick)
{
	std::map<std::string, Client*>::iterator  it = _clients_by_nick.find(nick);

	// std::cout << "server users: ";
	// for (const auto& pair : _clients_by_nick)
	// {
	// 	std::cout << pair.first << " ";
	// }
	// std::cout << std::endl;

	if (it != _clients_by_nick.end())
	{
		return (it->second);
	}
	else
		return (NULL);
}

void	Server::AddClient	(Client* client)
{
	_clients_by_nick		[client->GetNickname()] = client;
}

void	Server::RmvClient	(Client* client)
{
	_clients_by_nick.erase	(client->GetNickname());
}

//------------------------------------------------------------

//-------------------- Utility  Functions --------------------

bool	Server::IsNicknameAvailable	(const std::string& nickname) const
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

Client*	Server::FindUserByNickname	(const std::string& nickname) const
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

//------------------------------------------------------------

//--------------------   Getter Methods   --------------------

const std::string&	Server::GetPassword		() const	{ return _password;		}

const std::string&	Server::GetServerName	() const	{ return _server_name;	}
const std::string&	Server::GetNetwrkName	() const	{ return _netwrk_name;	}

PollHandler&		Server::GetPollHandler	()			{ return _poll_handlr;	}

//------------------------------------------------------------

//--------------------  Command Handling  --------------------

void	Server::SetupCommands()
{
	_cmds_handlr["INVITE"]	= new InviteCommand	(*this);

	_cmds_handlr["TOPIC"]	= new TopicCommand	(*this);

	_cmds_handlr["JOIN"]	= new JoinCommand	(*this);
	_cmds_handlr["MODE"]	= new ModeCommand	(*this);

	_cmds_handlr["PART"]	= new PartCommand	(*this);
	_cmds_handlr["KICK"]	= new KickCommand	(*this);

	_cmds_handlr["USER"]	= new UserCommand	(*this);
	_cmds_handlr["NICK"]	= new NickCommand	(*this);
	_cmds_handlr["PASS"]	= new PassCommand	(*this);

	_cmds_handlr["QUIT"]	= new QuitCommand	(*this);
	
	_cmds_handlr["PRIVMSG"]	= new PrivCommand	(*this);
}

//------------------------------------------------------------

//-------------------- Message Processing --------------------

void	Server::ProcessMessage			(Client* sender, const Message& msg)
{
	std::map<std::string, CommandHandler*>::iterator it = _cmds_handlr.find(msg.GetCommand());

	if (it != _cmds_handlr.end())
	{
		it->second->Execute(sender, msg);
	}
	else
	{
		Logger::getInstance().Log(WARNING, "Unknown command: " + msg.GetCommand() + " from FD " + ft_to_string(sender->GetFD()));
	}
}

void	Server::SendsNumericReply		(Client* user, int numeric, const std::string& message)
{
	std::stringstream ss;

	ss << ":" << _server_name << " " << std::setw(3) << std::setfill('0') << numeric << " " << user->GetNickname() << " " << message << "\r\n";

	user->AppendToOuputBuffer	(ss.str());

	_poll_handlr.SetEvents		(user->GetFD(), POLLIN | POLLOUT); //
}

void	Server::CheckRegistration		(Client* user)
{
	if (user->IsRegistered())
		return ;

	bool nick_set	= ( user->GetNickname() != "*");
	bool user_set	= (!user->GetUsername().empty() && !user->GetRealname().empty());

	bool pass_ok	= (_password.empty() || user->GetPassword() == _password);

	if (nick_set && user_set && pass_ok)
	{
		user->SetStatus		(REGISTERED);

		Logger::getInstance().Log(INFO, "User " + user->GetNickname() + " is now registered.");

		Logger::getInstance().Log(INFO, "User FD " + ft_to_string(user->GetFD()) + " (" + user->GetNickname() + ") is now registered!");

		SendsNumericReply	(user, 001, ":Welcome to the "	+ _netwrk_name + " IRC Network " + user->GetNickname() + "!" + user->GetUsername() + "@" + user->GetHostname());

		SendsNumericReply	(user, 002, ":Your host is "	+ _server_name + ", running version 1.0");
	}
}

void	Server::BroadcastChannelMessage	(Channel* channel, Client* sender, const std::string& message)
{
	std::map<int, Client*>::const_iterator	it;

	if (!channel)
		return ;

	const std::map<int, Client*>&	 users = channel->GetUsers();
	
	std::string	full_message = ":" + sender->GetNickname() + " " + message + "\r\n";

	for (it = users.begin(); it != users.end();  ++it)
	{
		std::cout << "Broadcasting message to " << it->second->GetNickname() << full_message;

		if (send(it->second->GetFD(), full_message.c_str(), full_message.length(), 0) < 0)
		{
			Logger::getInstance().Log(ERROR, "Sending message to client " + it->second->GetNickname() + ": " + strerror(errno));

            ClientDisconnection(it->second->GetFD());
		}
	}
}

//------------------------------------------------------------

void	Server::CheckForTimeouts()
{
	std::map<int, Client*>::iterator	it = _clients.begin();

	time_t	curr_time =  time(NULL);

	const int TIMEOUT_DURATION = 10;

	while (it != _clients.end())
	{
		Client*	user = it->second;

		if (!user->IsAuthenticated() && (curr_time - user->GetConnectionTime() > TIMEOUT_DURATION))
		{
			Logger::getInstance().Log(WARNING, "Client FD " + ft_to_string(user->GetFD()) + " timed out due to no password.");

			int fd_to_remove =  user->GetFD();

			ClientDisconnection(fd_to_remove);
		}
		it++;
	}
}

void	Server::cleanupClients()
{
	for (std::vector<int>::iterator it = _fdsToDelete.begin(); it != _fdsToDelete.end(); ++it)
	{
		int fd = *it;
		
		std::map<int, Client*>::iterator client_it = _clients.find(fd);

		if (client_it != _clients.end())
		{
			Client* client_ptr = client_it->second;

			delete client_ptr;
			_clients.erase(client_it);
		}

		_poll_handlr.RmvSocket(fd);
		
		close(fd);
	}
	_fdsToDelete.clear();
}

void	Server::cleanupChannels()
{
	for (std::vector<std::string>::iterator it = _channelsToDelete.begin(); it != _channelsToDelete.end(); ++it)
	{
		std::string channel_name = *it;

		std::map<std::string, Channel*>::iterator channel_it = _channels.find(channel_name);

		if (channel_it != _channels.end())
		{
			Channel* channel_ptr = channel_it->second;
			
			delete channel_ptr;
			_channels.erase(channel_it);
		}
	}
	_channelsToDelete.clear();
}
