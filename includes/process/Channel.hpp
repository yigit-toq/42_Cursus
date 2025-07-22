/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:35 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 23:12:06 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>

class Client;
class Server;

//bakılacak

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		size_t					_user_limit;
		bool					_invite_only;
		bool					_topic_set_by_op;

		std::map<int, Client*>	_users;
		std::map<int, Client*>	_operators;

		Server&					_server;

		Channel											(const Channel& other);
		Channel& operator=								(const Channel& other);

	public:
		 Channel										(const std::string& name, Server& server);
		~Channel										();

		const std::string&	GetName						() const;
		const std::string&	GetTopic					() const;
		const std::string&	GetPassword					() const;

		size_t GetUserLimit								() const;

		bool	IsInviteOnly							() const;
		bool	IsTopicSetByOp							() const;

		bool	IsUserInChannel							(Client* user) const;
		bool	IsOperator								(Client* user) const;

		const	std::map<int, Client*>& getUsers		() const;
		const	std::map<int, Client*>& getOperators	() const;

		void	SetTopic								(const std::string& topic, Client* setter = NULL);

		void	SetPassword								(const std::string& password);

		void	SetUserLimit							(size_t limit);

		void	SetInviteOnly							(bool status);
		void	SetTopicSetByOp							(bool status);

		void	AddUser									(Client* user);
		void	RmvUser									(Client* user);

		void	AddOperator								(Client* user);
		void	RmvOperator								(Client* user);

		void	BroadcastMessage						(const std::string& message, Client* exclude_user = NULL);

		bool	IsFull									() const;
		bool	IsEmpty									() const;
};

#endif
