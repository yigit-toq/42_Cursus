/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:03 by ytop              #+#    #+#             */
/*   Updated: 2025/08/06 18:28:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Channel.hpp"

#include <string>
#include <queue>
#include <map>

enum UserStatus
{
	UNREGISTERED,
	NICK_SET,
	USER_SET,
	REGISTERED
};

class Client
{
	private:
		int											_fd;

		std::map<char, bool>						_modes;

		UserStatus									_status;

		std::string									_nickname;
		std::string									_username;
		std::string									_realname;
		std::string									_hostname;
		std::string									_password;

		std::string									_input_buffer;
		std::string									_ouput_buffer;

		std::vector<Channel*>						_join_channels;

	public:
		 Client												(int fd);
		~Client												();

		int 							GetFD				() const;

		UserStatus						GetStatus			() const;

		std::string 					GetUsername			() const;
		std::string 					GetNickname			() const;
		std::string 					GetRealname			() const;
		std::string						GetHostname			() const;
		std::string						GetPassword			() const;

		std::string						GetModeString		() const;

		const std::string&				GetOutputBuffer		() const;

		const std::vector<Channel*>&	GetJoinChannels		() const;

		bool							IsModeSet			(char mode) const;

		bool							IsRegistered		() const;
		bool							HasOuputData		() const;

		void 							SetFD				(int fd);

		void							SetStatus			(UserStatus status);

		void 							SetUsername			(const std::string &username);
		void 							SetNickname			(const std::string &nickname);
		void 							SetRealname			(const std::string &realname);
		void 							SetHostname			(const std::string &hostname);
		void 							SetPassword			(const std::string &password);

		void 							AppendToInputBuffer	(const std::string &data);
		void 							AppendToOuputBuffer	(const std::string &data);

		void 							ApplyModes			(Client* sender, const std::string& mode_string, Server& server);

		void							AddChannel			(Channel* channel);
		void							RmvChannel			(Channel* channel);

		void							PopOutputBuffer		(size_t count);

		std::string						ExtractNextMessage	();

	private:
		void							handle_I_Mode		(char sign, Server& server);
		void							handle_W_Mode		(char sign, Server& server);
};

#endif
