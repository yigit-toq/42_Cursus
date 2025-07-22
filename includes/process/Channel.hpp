/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:35 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 16:17:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>

class Client;
class Server;

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_password;			// Kanal şifresi    (+k modu için)
		size_t					_user_limit;		// Kullanıcı limiti (+l modu için)
		bool					_invite_only;		// Davetiyeli kanal (+i modu için)
		bool					_topic_set_by_op;	// Konu sadece op'lar tarafından ayarlanabilir (+t modu için)

		std::map<int, Client*> 	_users;     // Kanaldaki tüm kullanıcılar (FD -> Client*)
		std::map<int, Client*> 	_operators; // Kanal operatörleri (FD -> Client*)

		// IRCServer referansı, kanalların sunucuyla etkileşim kurması gerektiğinde
		// (örneğin kullanıcıya hata mesajı gönderme, broadcast için)
		Server&				_server;

		// Kopyalama kurucusunu ve atama operatörünü engelle
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);

	public:
		 Channel(const std::string& name, Server& server);
		~Channel();

		// Getter Metotları
		const std::string& GetName() const;
		const std::string& GetTopic() const;
		const std::string& GetPassword() const;
		size_t GetUserLimit() const;
		bool IsInviteOnly() const;
		bool IsTopicSetByOp() const;

		// Kullanıcılar ve Operatörler için
		bool IsUserInChannel(Client* user) const;
		bool IsOperator(Client* user) const;
		const std::map<int, Client*>& getUsers() const; // Kanaldaki tüm kullanıcıları döndürür
		const std::map<int, Client*>& getOperators() const; // Kanal operatörlerini döndürür

		// Setter Metotları (modlar için)
		void SetTopic(const std::string& topic, Client* setter = NULL); // setter null ise sunucu set etti
		void SetPassword(const std::string& password);
		void SetUserLimit(size_t limit);
		void SetInviteOnly(bool status);
		void SetTopicSetByOp(bool status);

		// Kanal Üyeliği Metotları
		void AddUser(Client* user);
		void RemoveUser(Client* user);
		void AddOperator(Client* user);
		void RemoveOperator(Client* user); // Operatörlüğü kaldırır, kanalda kalabilir

		// Kanal İletişimi
		void BroadcastMessage(const std::string& message, Client* exclude_user = NULL);

		// Kanal durumu kontrol metotları
		bool IsFull() const;
		bool IsEmpty() const;
};

#endif
