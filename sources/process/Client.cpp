/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/07/20 18:44:29 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client:: Client	(int fd) : _fd(fd), _status(UNREGISTERED)
{
	_nickname = "*";
	_username = "";
	_realname = "";
	_hostname = "";
	_password = "";
}

Client::~Client	() {}

int		Client::GetFD() const { return _fd; }

void	Client::SetFD(int fd) { _fd = fd;	}

std::string Client::GetNickName					() const { return _nickname; }

std::string Client::GetUserName					() const { return _username; }

std::string Client::GetRealName					() const { return _realname; }

std::string Client::GetHostName					() const { return _hostname; }

std::string Client::GetPassword					() const { return _password; }

UserStatus Client::GetStatus					() const { return _status; } //

void Client::SetNickName						(const std::string &nickname)	{ _nickname = nickname; }

void Client::SetUserName						(const std::string &username)	{ _username = username; }

void Client::SetRealName						(const std::string &realname)	{ _realname = realname; }

void Client::SetHostName						(const std::string &hostname)	{ _hostname = hostname; }

void Client::SetPassword						(const std::string &password)	{ _password = password; }

void Client::SetStatus(UserStatus status)		{ _status = status; } //

void Client::AppendToInputBuffer				(const std::string &data)		{ _input_buffer += data;	}

void Client::AppendToOuputBuffer				(const std::string &data)		{ _ouput_buffer.push(data);	}

std::string Client::ExtrctNextMessage()
{
	size_t		pos		= _input_buffer.find	("\r\n");

	if (pos == std::string::npos)
		return ("");

	std::string	message	= _input_buffer.substr	(0, pos);

	_input_buffer.erase(0, pos + 2);

	return (message);
}

bool	Client::IsRegistered() const //
{
	return (_status == REGISTERED);
}

bool	Client::HasOuputData() const //
{
	return (!_ouput_buffer.empty());
}

std::string Client::NextOutputMessage() //
{
	if (_ouput_buffer.empty())
		return ("");

	std::string message = _ouput_buffer.front();
	_ouput_buffer.pop();

	return (message);
}
