#ifndef SERVER_HPP
#define SERVER_HPP

#include <iomanip>
#include <cstring>

#include <unistd.h>

#include "Socket.hpp"
#include "Client.hpp"

#include "PollHandler.hpp"

#include "UserCommand.hpp"
#include "QuitCommand.hpp"
#include "PrivCommand.hpp"
#include "PassCommand.hpp"
#include "PartCommand.hpp"
#include "NickCommand.hpp"
#include "ModeCommand.hpp"
#include "KickCommand.hpp"
#include "JoinCommand.hpp"
#include "TopicCommand.hpp"
#include "InviteCommand.hpp"

#define BUFFER_SIZE	512

class Server
{
	private:
		std::map<std::string, CommandHandler*>		_cmds_handler;
		PollHandler									_poll_handler;

		Socket										_srvr_socket ;

		std::string									_server_name ;
		std::string									_netwrk_name ;

		std::string									_password;

		std::map	<std::string, Channel*>			_channels;
		std::map	<int, Client*>					_clients;

		std::vector	<int>							_usersToDelete;
		std::vector	<std::string>					_chnlsToDelete;

		std::map	<std::string, Client*>			_clients_by_nick;

	private:
		Server											(const Server&);
		Server& operator=								(const Server&);

		void				HandleEvents				(const std::vector<struct pollfd>& active_fds);

		void				HandleServerSocketEvent		(const struct pollfd& server_fd);
		void				HandleClientSocketEvent		(const struct pollfd& client_fd);

		void				HandleClientREvent			(int fd, Client* user);
		void				HandleClientWEvent			(int fd, Client* user);

		void				ProcessMessage				(Client* sender, const Message& msg);
		void				SetupCommands				();

		void				CleanupUsers				();
		void				CleanupChnls				();

		void				CheckForTimeout				();

	public:
		 Server											(int port, std::string pass);
		~Server											();

		void				Start						();

		const std::string	GetHostname					(int fd);

		const std::string&	GetPassword					() const;

		const std::string&	GetServerName				() const;
		const std::string&	GetNetwrkName				() const;

		PollHandler&		GetPollHandler				();

		Client*				FindUserByNick				(const std::string& nickname) const;
		bool				IsNicknameAval				(const std::string& nickname) const;

		void 				CheckRegistration			(Client* user);
		void 				SendsNumericReply			(Client* user, int numeric, const std::string& data);
	
		void 				HandleNewConnection			();
		void 				HandleClientMessage			(int fd);
		void 				ClientDisconnection			(int fd);

		void				AddUser						(Client* user);
		void				RmvUser						(Client* user);

		Client*				FindUser					(const std::string& nick);

		Channel*			FinderChannel				(const std::string& name) const;
		Channel*			CreateChannel				(const std::string& name);

		void				RemoveChannel				(const std::string& name);

		void				BroadcastChannelMessage		(Channel* channel, Client* sender, const std::string& message);

		void				BroadcastNicknameChange		(Client* client, const std::string& old_nick, const std::string& new_nick);

};

#endif
