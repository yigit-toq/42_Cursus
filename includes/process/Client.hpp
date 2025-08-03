/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:03 by ytop              #+#    #+#             */
/*   Updated: 2025/08/03 21:18:35 by ytop             ###   ########.fr       */
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

		UserStatus									_status;

		std::string									_nickname;
		std::string									_username;
		std::string									_realname;
		std::string									_hostname;
		std::string									_password;

		std::string									_input_buffer;
		std::string									_ouput_buffer;

		std::vector<Channel*>						_joined_channels;

		std::map<char, bool>						_modes; //

	public:
		 Client												(int fd);
		~Client												();

		int 							GetFD				() const;

		UserStatus						GetStatus			() const;

		std::string 					GetUserName			() const;
		std::string 					GetNickName			() const;
		std::string 					GetRealName			() const;
		std::string						GetHostName			() const;
		std::string						GetPassword			() const;

		const std::string&				GetOutputBuffer		() const;

		const std::vector<Channel*>&	GetJoinedChannels	() const;

		bool							IsRegistered		() const;
		bool							HasOuputData		() const;

		void 							SetFD				(int fd);

		void							SetStatus			(UserStatus status);

		void 							SetUserName			(const std::string &username);
		void 							SetNickName			(const std::string &nickname);
		void 							SetRealName			(const std::string &realname);
		void 							SetHostName			(const std::string &hostname);
		void 							SetPassword			(const std::string &password);

		void 							AppendToInputBuffer	(const std::string &data);
		void 							AppendToOuputBuffer	(const std::string &data);

		void							AddChannel			(Channel* channel);
		void							RmvChannel			(Channel* channel);

		void							PopOutputBuffer		(size_t count);

		std::string						ExtractNextMessage	();

		// Yeni eklenen metotlar
		bool IsModeSet(char mode_char) const;
		std::string GetModeString() const;
		void ApplyModes(Client* sender, const std::string& mode_string, Server& server);

	private:
		// Her mod için özel işleyici metotlar
		void handleInvisibleMode(char sign, Server& server);
		void handleWallopsMode(char sign, Server& server);
		// Diğer modlar için de benzer metotlar eklenebilir
};

#endif
