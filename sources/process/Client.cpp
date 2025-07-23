/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 17:55:18 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream> //

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

void Client::AppendToOuputBuffer(const std::string& data)
{
    _ouput_buffer.append(data);
    std::cout << "User " << GetNickName() << " appended " << data.length()
              << " bytes to output buffer. Total size: " << _ouput_buffer.length() << std::endl;
}

std::string Client::ExtractNextMessage()
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

const std::string& Client::PeekOutputBuffer() const
{
    return _ouput_buffer; // Tamponun tamamını döndürüyor, `send` bunu kullanacak.
}

void Client::popOutputBuffer(size_t count)
{
	if (count <= _ouput_buffer.length()) {
		_ouput_buffer.erase(0, count);
		std::cout << "User " << GetNickName() << " popped " << count << " bytes from output buffer. Remaining: "
				<< _ouput_buffer.length() << std::endl;
	} else {
		_ouput_buffer.clear(); // Hata durumunda veya count fazla gelirse tümünü temizle
		std::cout << "User " << GetNickName() << " output buffer cleared." << std::endl;
	}
}

void Client::AddChannel(Channel* channel)
{
	// Kanal zaten ekliyse tekrar ekleme
	for (size_t i = 0; i < _joined_channels.size(); ++i) {
		if (_joined_channels[i] == channel) {
			return;
		}
	}
	_joined_channels.push_back(channel);
	std::cout << "Client " << _nickname << " added to joined channel list: " << channel->GetName() << std::endl;
}

void Client::RemoveChannel(Channel* channel)
{
	for (std::vector<Channel*>::iterator it = _joined_channels.begin(); it != _joined_channels.end(); ++it) {
		if (*it == channel) {
			_joined_channels.erase(it);
			std::cout << "Client " << _nickname << " removed from joined channel list: " << channel->GetName() << std::endl;
			return;
		}
	}
}

const std::vector<Channel*>& Client::GetJoinedChannels() const
{
	return _joined_channels;
}
