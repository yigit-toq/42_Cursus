/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:35 by ytop              #+#    #+#             */
/*   Updated: 2025/08/06 21:50:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <map>

class Client;
class Server;

//bakılacak

class Channel
{
	private:
		std::string										_name;
		std::string										_pass;
		std::string										_topic;

		std::map<char, bool>							_modes;

		size_t											_user_limit;

		bool											_invite_only;
		bool											_topic_by_op;

		std::map<int, Client*>							_users;
		std::map<int, Client*>							_operators;

		std::vector<std::string>						_invited_users; //

		Server&											_server;

		Channel											(const Channel& other);
		Channel& operator=								(const Channel& other);

	public:
		 Channel										(const std::string& name, Server& server);
		~Channel										();

		const std::string&	GetName						() const;
		const std::string&	GetPass						() const;
		const std::string&	GetTopic					() const;

		std::string	GetModeString						() const;
		std::string	GetModeParams						() const;

		size_t	GetUserLimit							() const;

		bool	IsInviteOnly							() const;
		bool	IsTopicSetOp							() const;

		bool	IsUser									(Client* user)	const;
		bool	IsOperator								(Client* user)	const;

		bool	IsModeSet								(char mode)		const;

		const	std::map<int, Client*>& GetUsers		() const;
		const	std::map<int, Client*>& GetOperators	() const;

		void	SetName									(const std::string& name);
		void	SetPass									(const std::string& pass);
		void	SetTopic								(const std::string& topic, Client* setter = NULL);

		void	SetUserLimit							(size_t limit);

		void	SetInviteOnly							(bool status);
		void	SetTopicSetOp							(bool status);

		void	BroadcastMessage						(const std::string& message, Client* exclude_user = NULL);

		bool	IsFull									() const;
		bool	IsEmpty									() const;

		void	AddInvitedUser							(const std::string& nickname); //
		void	RemoveInvitedUser						(const std::string& nickname); //
		bool	IsUserInvited							(const std::string& nickname) const; //

		void	AddClient								(Client* user);
		void	RmvClient								(Client* user);

		void	AddOperator								(Client* user);
		void	RmvOperator								(Client* user);

		void	ApplyModes								(Client* sender, const std::string& mode_strs, const std::vector<std::string>& mode_args, Server& server);

	private:
		void	handle_I_Mode							(Client* sender, char sign);
		void	handle_T_Mode							(Client* sender, char sign);
		void	handle_K_Mode							(Client* sender, char sign, const std::string& param);
		void	handle_L_Mode							(Client* sender, char sign, const std::string& param);
		void	handle_O_Mode							(Client* sender, char sign, const std::string& param);
};

#endif
