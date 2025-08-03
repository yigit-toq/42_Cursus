/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:35 by ytop              #+#    #+#             */
/*   Updated: 2025/08/03 20:17:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <functional>

class Client;
class Server;

//bakilacak

class Channel
{
	private:
		std::string										_name;
		std::string										_pass;
		std::string										_topic;

		size_t											_user_limit;

		bool											_invite_only;
		bool											_topic_set_by_op;

		std::map<int, Client*>							_clients;
		std::map<int, Client*>							_operators;

		Server&											_server;

		std::map<char, bool>							_modes; //
		long long										_creation_time; //

		Channel											(const Channel& other);
		Channel& operator=								(const Channel& other);

	public:
		 Channel										(const std::string& name, Server& server);
		~Channel										();

		const std::string&	GetName						() const;
		const std::string&	GetPass						() const;
		const std::string&	GetTopic					() const;

		size_t	GetUserLimit							() const;

		bool	IsInviteOnly							() const;
		bool	IsTopicSetByOp							() const;

		bool	IsUser									(Client* user) const;
		bool	IsOperator								(Client* user) const;

		const	std::map<int, Client*>& getUsers		() const;
		const	std::map<int, Client*>& getOperators	() const;

		void	SetName									(const std::string& name);
		void	SetPass									(const std::string& pass);
		void	SetTopic								(const std::string& topic, Client* setter = NULL);

		void	SetUserLimit							(size_t limit);

		void	SetInviteOnly							(bool status);
		void	SetTopicSetByOp							(bool status);

		void	BroadcastMessage						(const std::string& message, Client* exclude_user = NULL);

		bool	IsFull									() const;
		bool	IsEmpty									() const;

		void	AddClient								(Client* user);
		void	RmvClient								(Client* user);

		void	AddOperator								(Client* user);
		void	RmvOperator								(Client* user);

		bool IsModeSet(char mode_char) const; //

		// Yeni MODE komutu için metotlar
		std::string GetModeString	() const; // Kanalın modlarını bir string olarak döndürür (örn. "+it")
		std::string GetModeParams	() const; // Kanalın mod parametrelerini döndürür (örn. "anahtar 10")
		void ApplyModes				(Client* sender, const std::string& mode_string, const std::vector<std::string>& mode_args, Server& server);

	private:
		static bool IsChannelModeWithParameter(char mode_char);

		void handleInviteOnlyMode	(Client* sender, char sign); //
		void handleTopicMode		(Client* sender, char sign); //
		void handleKeyMode			(Client* sender, char sign, const std::string& param); //
		void handleLimitMode		(Client* sender, char sign, const std::string& param); //
		void handleOperatorMode		(Client* sender, char sign, const std::string& param); //
};

#endif
