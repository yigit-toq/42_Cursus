/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 08:15:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#pragma region header

#include <map>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "Socket.hpp"
#include "Client.hpp"

#include "Channel.hpp"
#include "Message.hpp"

#include "PollHandler.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "PassCommand.hpp"
#include "JoinCommand.hpp"
#include "PrivCommand.hpp"
#include "PartCommand.hpp"
#include "QuitCommand.hpp"
#include "KickCommand.hpp"
#include "ModeCommand.hpp"
#include "TopicCommand.hpp"
#include "InviteCommand.hpp"

#include "CommandHandler.hpp"

#pragma endregion

#define BUFFER_SIZE	512

//bakilacak

class Server
{
	private:
		std::map<std::string, CommandHandler*>		_cmds_handlr;
		PollHandler									_poll_handlr;

		Socket										_srvr_socket;

		std::string									_server_name;
		std::string									_netwrk_name;

		std::map<std::string, Client*>				_clients_by_nick;

		std::string									_password;

		std::map<std::string, Channel*>				_channels;
		std::map<int, Client*>						_clients;

		void	SetupCommands						();
		void	ProcessMessage						(Client* sender, const Message& msg);

		Server										(const Server&);
		Server& operator=							(const Server&);

		void	HandleEvents			(const std::vector<struct pollfd>& active_fds); //
		void	HandleServerSocketEvent	(const struct pollfd& server_fd); //
		void	HandleClientSocketEvent	(const struct pollfd& client_fd); //
		void	HandleClientReadEvent	(int client_fd, Client* user); //
		void	HandleClientWriteEvent	(int client_fd, Client* user); //

		void	CheckForTimeouts(); //

	public:
		 Server										(int port, std::string pass);
		~Server										();

		void Start									();

		const std::string&	GetPassword				() const;

		const std::string&	GetServerName			() const;
		const std::string&	GetNetwrkName			() const;

		Client*			FindUserByNickname			(const std::string& nickname) const;
		bool			IsNicknameAvailable			(const std::string& nickname) const;

		void 			CheckRegistration			(Client* user);
		void 			SendsNumericReply			(Client* user, int numeric, const std::string& data);
	
		void 			HandleNewConnection			();
		void 			HandleClientMessage			(int fd);
		void 			ClientDisconnection			(int fd);

		Client*			FindClient					(const std::string& nick);

		Channel*		FinderChannel				(const std::string& name) const;
		Channel*		CreateChannel				(const std::string& name);

		void			RemoveChannel				(const std::string& name);

		PollHandler&	GetPollHandler				();

		void			BroadcastChannelMessage		(Channel* channel, Client* sender, const std::string& message);

		void			AddClient					(Client* user); //
		void			RmvClient					(Client* user); //

		void			BroadcastNicknameChange(Client* client, const std::string& old_nick, const std::string& new_nick)
		{
			for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
			{
				Channel* channel = it->second;

				if (channel->IsUser(client))
				{
					std::stringstream ss;
					ss << ":" << old_nick << " NICK " << new_nick << "\r\n";
					channel->BroadcastMessage(ss.str(), NULL);
				}
			}
		}
};

#endif
