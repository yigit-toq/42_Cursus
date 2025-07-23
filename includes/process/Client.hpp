/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:03 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 17:54:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <queue>
#include "Channel.hpp"

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

	public:
		 Client										(int fd);

		~Client										();

		int 					GetFD				() const;

		UserStatus				GetStatus			() const;

		std::string 			GetUserName			() const;
		std::string 			GetNickName			() const;
		std::string 			GetRealName			() const;
		std::string				GetHostName			() const;
		std::string				GetPassword			() const;

		bool					IsRegistered		() const;
		bool					HasOuputData		() const;

		void 					SetFD				(int fd);

		void					SetStatus			(UserStatus status);

		void 					SetUserName			(const std::string &username);
		void 					SetNickName			(const std::string &nickname);
		void 					SetRealName			(const std::string &realname);
		void 					SetHostName			(const std::string &hostname);
		void 					SetPassword			(const std::string &password);

		void 					AppendToInputBuffer	(const std::string &data);
		void 					AppendToOuputBuffer	(const std::string &data);

		//bakılacak
		std::string				ExtractNextMessage	();

		const std::string&		PeekOutputBuffer	() const;
		void					popOutputBuffer		(size_t count);

		// Yeni: Kanalları yönetmek için metotlar
		void							AddChannel			(Channel* channel);
		void							RemoveChannel		(Channel* channel); // PART komutunda da kullanıldı, şimdi gerçek implementasyon gelecek
		const std::vector<Channel*>&	GetJoinedChannels	() const; // Yeni getter
};

#endif
