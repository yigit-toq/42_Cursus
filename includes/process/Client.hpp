/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:03 by ytop              #+#    #+#             */
/*   Updated: 2025/06/27 17:55:18 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
	private:
		int				_fd;

		std::string		_nickname;
		std::string		_username;
		std::string		_realname;
		std::string		_hostname;

		std::string		_input_buffer;
		std::string		_otput_buffer;

		bool			_isAuthenticated;

	public:
		 Client						(int fd);

		~Client						();

		int GetFd					() const;

		std::string GetUserName		() const;
		std::string GetNickName		() const;
		std::string GetRealName		() const;
		std::string GetHostName		() const;

		std::string GetInputBuffer	() const;
		std::string GetOtputBuffer	() const;

		bool		IsAuthenticated	() const;

		void 		SetFd			(int fd);

		void 		SetUserName			(const std::string &username);
		void 		SetNickName			(const std::string &nickname);
		void 		SetRealName			(const std::string &realname);
		void 		SetHostName			(const std::string &hostname);

		void 		AppendToInputBuffer	(const std::string &data);
		void 		AppendToOtputBuffer	(const std::string &data);

		void 		SetAuthenticated	(bool authenticated);

		void 		ClearOutputBuffer	();

		std::string	ExtractNextMessage	();
};

#endif
