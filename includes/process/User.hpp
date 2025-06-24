/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:02:24 by ytop              #+#    #+#             */
/*   Updated: 2025/06/24 17:29:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

class User
{
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		bool _isAuthenticated;
		std::string _input_buffer;
		std::string _output_buffer;

	public:
		User (int fd);

		~User();

		int GetFd() const;
		std::string GetNickname() const;
		std::string GetUsername() const;
		std::string GetRealname() const;
		std::string GetHostname() const;

		bool IsAuthenticated() const;

		std::string GetInputBuffer() const;
		std::string GetOutputBuffer() const;

		void SetFd(int fd);
		void SetNickname(const std::string &nickname);
		void SetUsername(const std::string &username);
		void SetRealname(const std::string &realname);
		void SetHostname(const std::string &hostname);

		void SetAuthenticated(bool authenticated);

		void AppendToInputBuffer(const std::string &data);
		void AppendToOutputBuffer(const std::string &data);

		void ClearOutputBuffer();

		std::string ExtractNextMessage();
};

#endif
