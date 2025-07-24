/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:48 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 18:00:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#pragma region header

#include <map>
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
#include "TopicCommand.hpp"
#include "CommandHandler.hpp"

#pragma endregion

#define BUFFER_SIZE	512

//bakilacak

class Server
{
	private:
		std::map<std::string, CommandHandler*>	_cmds_handlr;
		PollHandler								_poll_handlr;

		Socket									_srvr_socket;

		std::string								_server_name;
		std::string								_netwrk_name;

		std::string								_password;

		std::map<std::string, Channel*>			_channels;
		std::map<int, Client*>					_clients;

		void	SetupCommands					();
		void	ProcessMessage					(Client* sender, const Message& msg);

		Server									(const Server&);
		Server& operator=						(const Server&);

	public:
		 Server								(int port, std::string pass);
		~Server								();

		void Start							();

		const std::string&	GetServerName	() const;
		const std::string&	GetNetwrkName	() const;

		const std::string&	GetPassword		() const;

		Client*			FindUserByNickname			(const std::string& nickname) const;
		bool			IsNicknameAvailable			(const std::string& nickname) const;

		void 			CheckRegistration			(Client* user);
		void 			SendsNumericReply			(Client* user, int numeric, const std::string& data) const;
	
		void 			HandleNewConnection			();
		void 			HandleClientMessage			(int fd);
		void 			ClientDisconnection			(int fd);

		Channel*		FinderChannel				(const std::string& name) const;
		Channel*		CreateChannel				(const std::string& name);
		void			RemoveChannel				(const std::string& name);

		PollHandler&	GetPollHandler				();
};

#endif
