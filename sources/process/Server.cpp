#include "Server.hpp"

Server:: Server(int port, std::string pass) : _srvr_socket(port), _password(pass)
{
	_srvr_socket .Create	();
	_srvr_socket .Binder	();
	_srvr_socket .Listen	();

	_poll_handler.AddSocket	(_srvr_socket.GetSock(), POLLIN);

	SetupCommands			();

	_netwrk_name = "irc_network"	;
	_server_name = "irc.example.com";

	Logger::GetInstance().Log(INFO, "Server initialized on port " + ft_to_string(port) + " with password: " + pass);
}

Server::~Server()
{
	for (std::map<int, Client*>::iterator					it = _clients.		begin(); it != _clients.		end(); ++it)
	{
		delete (it->second);
	}
	_clients.		clear();

	for (std::map<std::string, Channel*>::iterator			it = _channels.		begin(); it != _channels.		end(); ++it)
	{
		delete (it->second);
	}
	_channels.		clear();

	for (std::map<std::string, CommandHandler*>::iterator	it = _cmds_handler.	begin(); it != _cmds_handler.	end(); ++it)
	{
		delete (it->second);
	}
	_cmds_handler.	clear();

	Logger::GetInstance().Log(INFO, "Server shutting down.");
}

//-------------------- Server Main Loop --------------------

void	Server::Start(void)
{
	while (true)
	{
		std::vector<struct pollfd> active_fds = _poll_handler.WaitForEvents(1000);

		HandleEvents	(active_fds);

		CleanupUsers	();
		CleanupChnls	();

		CheckForTimeout	();
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
		Logger::GetInstance().Log(ERROR, "User not found for FD " + ft_to_string(fd));

		_poll_handler.RmvSocket	(fd);

		return ;
	}

	if (client_fd.revents & (POLLERR | POLLHUP | POLLNVAL))
	{
		Logger::GetInstance().Log	(ERROR, "Client FD " + ft_to_string(fd) + " error or hangup.");

		ClientDisconnection			(fd);

		return ;
	}

	if ( client_fd.revents & POLLIN )
	{
		HandleClientREvent	(fd, user);
	}

	if ((client_fd.revents & POLLOUT) && user->HasOuputData())
	{
		HandleClientWEvent	(fd, user);
	}
}

void	Server::HandleClientREvent(int fd, Client* user)
{
	HandleClientMessage(fd);

	(void)user;
}

void	Server::HandleClientWEvent(int fd, Client* user)
{
	while (user->HasOuputData())
	{
		const std::string& data_to_send = user->GetOutputBuffer();

		int bytes_sent = _srvr_socket.Sender(user->GetFD(), (char *)data_to_send.c_str(), data_to_send.length());

		if (bytes_sent <= 0)
		{
			if (bytes_sent == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
			{
				Logger::GetInstance().Log(WARNING, "Send  buffer full for FD " + ft_to_string(user->GetFD()) + ", will try again next poll.");
			}
			else
			{
				Logger::GetInstance().Log(ERROR  , "Error sending data to FD " + ft_to_string(user->GetFD()) + ": " + strerror(errno));

				ClientDisconnection(user->GetFD());
			}
			break ;
		}
	
		user->PopOutputBuffer		(bytes_sent);

		Logger::GetInstance().Log	(INFO, "Sent " + ft_to_string(bytes_sent) + " bytes to FD " + ft_to_string(user->GetFD()) + ". Remaining: " + ft_to_string(user->GetOutputBuffer().length()) + " bytes.");
	}

	if (!user->HasOuputData())
	{
		_poll_handler.SetEvents		(user->GetFD(), POLLIN);

		Logger::GetInstance().Log	(INFO, "FD   " + ft_to_string(user->GetFD()) + " output buffer empty. POLLOUT removed.");
	}

	(void)fd;
}

void	Server::HandleNewConnection()
{
	int client_fd = _srvr_socket.Accept();

	if (client_fd < 0)
	{
		Logger::GetInstance().Log(ERROR, "Failed to accept new connection: " + std::string(strerror(errno)));
		return ;
	}

	Client* new_user = new Client(client_fd);

	new_user->SetHostname("irc.example.com");

	_clients[client_fd] = new_user;

	_poll_handler.AddSocket		(client_fd, POLLIN | POLLOUT);

	Logger::GetInstance().Log	(INFO, "New connection accepted: FD " + ft_to_string(client_fd));
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

			Logger::GetInstance().Log(INFO, "Received " + ft_to_string(bytes_read) + " bytes from FD " + ft_to_string(fd) + ": [" + buffer + "]");

			std::string	raw;

			while ((raw = user->ExtractNextMessage()) != "")
			{
				Logger::GetInstance().Log(INFO, "Full message extracted: " + raw);

				Message	msg;

				if (msg.Parse(raw))
				{
					// msg.Print();

					ProcessMessage(user, msg);
				}
				else
				{
					Logger::GetInstance ().Log(ERROR, "Failed to parse message from FD " + ft_to_string(fd) + ": " + raw);

					SendsNumericReply	(user, 421, msg.GetCommand() + " :Unknown command");
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
		Logger::GetInstance().Log(ERROR, "Error reading from client FD " + ft_to_string(fd) + ": " + strerror(errno));

		ClientDisconnection(fd);
	}
}

void	Server::ClientDisconnection(int fd)
{
	std::map<int, Client*>::iterator it = _clients.find(fd);

	if (it == _clients.end())
	{
		return ;
	}

	Client* client_ptr = it->second;

	std::vector<Channel *> joined_channels = client_ptr->GetJoinChannels(); 

	for (size_t i = 0; i < joined_channels.size(); ++i)
	{
		Channel *channel_ptr = joined_channels[i];
		
		if (channel_ptr)
		{
			channel_ptr->RmvUser(client_ptr);
		}
	}

	_usersToDelete.push_back(fd);

	Logger::GetInstance().Log(INFO, "Client FD " + ft_to_string(fd) + " disconnected. Removing from server.");
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
	if (FinderChannel			(name) != NULL)
	{
		Logger::GetInstance		().Log(WARNING, "Attempted to create already existing channel: " + name);

		return (FinderChannel	(name));
	}

	Channel* new_channel	= new Channel(name, *this);

	_channels[name]			= new_channel;

	Logger::GetInstance().Log(INFO, "Created new channel: " + name);

	return (new_channel);
}

void	Server::RemoveChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);

	if (it == _channels.end())
	{
		return;
	}

	_chnlsToDelete.push_back (name);

	Logger::GetInstance().Log(INFO, "Channel " + name + " marked for deletion.");
}

//------------------------------------------------------------

//-------------------- Client  Management --------------------

Client*	Server::FindUser	(const std::string& nick)
{
	std::map<std::string, Client*>::iterator  it = _clients_by_nick.find(nick);

	if (it != _clients_by_nick.end())
	{
		return (it->second);
	}
	else
	{
		return (NULL);
	}
}

void	Server::AddUser		(Client* client)
{
	_clients_by_nick		[client->GetNickname()] = client;
}

void	Server::RmvUser		(Client* client)
{
	_clients_by_nick.erase	(client->GetNickname());
}

//------------------------------------------------------------

//-------------------- Utility  Functions --------------------

bool	Server::IsNicknameAval	(const std::string& nickname) const
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

	return (FindUserByNick(nickname) == NULL);
}

Client*	Server::FindUserByNick	(const std::string& nickname) const
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

PollHandler&		Server::GetPollHandler	()			{ return _poll_handler;	}

//------------------------------------------------------------

//--------------------  Command Handling  --------------------

void	Server::SetupCommands()
{
	_cmds_handler["INVITE"]		= new InviteCommand	(*this);

	_cmds_handler["TOPIC"]		= new TopicCommand	(*this);

	_cmds_handler["USER"]		= new UserCommand	(*this);
	_cmds_handler["NICK"]		= new NickCommand	(*this);
	_cmds_handler["PASS"]		= new PassCommand	(*this);

	_cmds_handler["JOIN"]		= new JoinCommand	(*this);
	_cmds_handler["MODE"]		= new ModeCommand	(*this);

	_cmds_handler["PART"]		= new PartCommand	(*this);
	_cmds_handler["KICK"]		= new KickCommand	(*this);
	_cmds_handler["QUIT"]		= new QuitCommand	(*this);
	
	_cmds_handler["PRIVMSG"]	= new PrivCommand	(*this);
}

//------------------------------------------------------------

//-------------------- Message Processing --------------------

void	Server::ProcessMessage			(Client* sender, const Message& msg)
{
	std::map<std::string, CommandHandler*>::iterator it = _cmds_handler.find(msg.GetCommand());

	if (it != _cmds_handler.end	())
	{
		it->second->Execute		(sender, msg);
	}
	else
	{
		Logger::GetInstance		().Log(WARNING, "Unknown command: " + msg.GetCommand() + " from FD " + ft_to_string(sender->GetFD()));
	}
}

void	Server::SendsNumericReply		(Client* user, int numeric, const std::string& message)
{
	std::stringstream ss;

	ss << ":" << _server_name << " " << std::setw(3) << std::setfill('0') << numeric << " " << user->GetNickname() << " " << message << "\r\n";

	user->AppendToOuputBuffer	(ss.str());

	_poll_handler.	SetEvents	(user->GetFD(), POLLIN | POLLOUT);
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

		SendsNumericReply	(user,  001, ":Welcome to the "	+ _netwrk_name + " IRC Network " + user->GetNickname() + "!" + user->GetUsername() + "@" + user->GetHostname());

		Logger::GetInstance	().Log(INFO, "User " + user->GetNickname() + " is now registered.");
	}
}

void	Server::BroadcastChannelMessage	(Channel* channel, Client* sender, const std::string& message)
{
	std::map<int, Client*>::const_iterator	it;

	if (!channel)
		return ;

	const std::map<int, Client*>&	 users = channel->GetUsers();
	
	std::string	full_message = ":" + sender->GetNickname() + " " + message + "\r\n";

	for (it = users.begin(); it != users.end(); ++it)
	{
			Logger::GetInstance().Log(INFO , "Broadcasting message to " + it->second->GetNickname() + ": " + full_message	);

		if (send(it->second->GetFD(), full_message.c_str(), full_message.length(), 0) < 0)
		{
			Logger::GetInstance().Log(ERROR, "Send message to  client " + it->second->GetNickname() + ": " + strerror(errno));

			ClientDisconnection(it->second->GetFD());
		}
	}
}

void	Server::BroadcastNicknameChange	(Client* client, const std::string& old_nick, const std::string& new_nick)
{
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		Channel* channel = it->second;

		if (channel->IsUser(client))
		{
			std::stringstream ss;

			ss << ":" << old_nick << " NICK " << new_nick << "\r\n";

			channel->BroadcastMsg(ss.str(), NULL);
		}
	}
}

//------------------------------------------------------------

void	Server::CheckForTimeout	()
{
	std::map<int, Client*>::iterator	it = _clients.begin();

	time_t	curr_time =  time(NULL);

	const int TIMEOUT_DURATION = 10;

	while (it != _clients.end())
	{
		Client*	user = it->second;

		if (!user->GetAuth() && (curr_time - user->GetConnectionTime() > TIMEOUT_DURATION))
		{
			Logger::GetInstance().Log(WARNING, "Client FD " + ft_to_string(user->GetFD()) + " timed out due to no password.");

			int fd_to_remove =  user->GetFD();

			ClientDisconnection(fd_to_remove);
		}
		it++;
	}
}

void	Server::CleanupChnls()
{
	for (std::vector<std::string>::iterator it = _chnlsToDelete.begin(); it != _chnlsToDelete.end(); ++it)
	{
		std::string channel_name = *it;

		std::map<std::string, Channel*>::iterator channel_it = _channels.find(channel_name);

		if (channel_it != _channels.end())
		{
			Channel* channel_ptr = channel_it->second;
			
			delete			(channel_ptr);

			_channels.erase	(channel_it );
		}
	}

	_chnlsToDelete.clear	();
}

void	Server::CleanupUsers()
{
	for (std::vector<int>::iterator it = _usersToDelete.begin(); it != _usersToDelete.end(); ++it)
	{
		int fd = *it;
		
		std::map<int, Client*>::iterator client_it = _clients.find(fd);

		if (client_it != _clients.end())
		{
			Client* client_ptr = client_it->second;

			delete			(client_ptr);

			_clients.erase	(client_it );
		}

		_poll_handler.RmvSocket(fd);
		
		close(fd);
	}
	_usersToDelete.clear();
}

//------------------------------------------------------------
