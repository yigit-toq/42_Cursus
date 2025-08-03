/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/08/03 21:21:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

Client:: Client	(int fd) : _fd(fd), _status(UNREGISTERED)
{
	_nickname = "*";
	_username = "";
	_realname = "";
	_hostname = "";
	_password = "";

	_modes['i'] = false;
	_modes['w'] = false;
	_modes['o'] = false;
}

Client::~Client	() {}

int		Client::GetFD() const { return _fd; }

void	Client::SetFD(int fd) { _fd = fd;	}

std::string Client::GetNickName					() const { return _nickname; }
std::string Client::GetUserName					() const { return _username; }
std::string Client::GetRealName					() const { return _realname; }
std::string Client::GetHostName					() const { return _hostname; }
std::string Client::GetPassword					() const { return _password; }

void	Client::SetNickName						(const std::string &nickname)	{ _nickname = nickname; }
void	Client::SetUserName						(const std::string &username)	{ _username = username; }
void	Client::SetRealName						(const std::string &realname)	{ _realname = realname; }
void	Client::SetHostName						(const std::string &hostname)	{ _hostname = hostname; }
void	Client::SetPassword						(const std::string &password)	{ _password = password; }

void	Client::AppendToInputBuffer				(const std::string &data)		{ _input_buffer += data; }

void	Client::AppendToOuputBuffer				(const std::string& data)
{
	_ouput_buffer.append(data);

	std::cout << "User " << GetNickName() << " appended " << data.length() << " bytes to output buffer. Total size: " << _ouput_buffer.length() << std::endl;
}

bool	Client::IsRegistered() const
{
	return (_status == REGISTERED);
}

bool	Client::HasOuputData() const
{
	return (!_ouput_buffer.empty());
}

void	Client::PopOutputBuffer(size_t count)
{
	if (count <= _ouput_buffer.length())
	{
		_ouput_buffer.erase(0, count);

		std::cout << "User " << GetNickName() << " popped " << count << " bytes from output buffer. Remaining: " << _ouput_buffer.length() << std::endl;
	}
	else
	{
		_ouput_buffer.clear();

		std::cout << "User " << GetNickName() << " output buffer cleared." << std::endl;
	}
}

void	Client::AddChannel(Channel* channel)
{
	for (size_t i = 0; i < _joined_channels.size(); ++i)
	{
		if (_joined_channels[i] == channel)
			return ;
	}
	_joined_channels.push_back(channel);

	std::cout << "Client " << _nickname << " added to joined channel list: " << channel->GetName() << std::endl;
}

void	Client::RmvChannel(Channel* channel)
{
	for (std::vector<Channel*>::iterator it = _joined_channels.begin(); it != _joined_channels.end(); ++it)
	{
		if (*it == channel)
		{
			_joined_channels.erase(it);

			std::cout << "Client " << _nickname << " removed from joined channel list: " << channel->GetName() << std::endl;

			return ;
		}
	}
}

const std::vector<Channel*>&	Client::GetJoinedChannels	() const
{
	return (_joined_channels);
}

const std::string&				Client::GetOutputBuffer		() const
{
	return (_ouput_buffer);
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

void		Client::SetStatus(UserStatus status)	{ _status = status;	}

UserStatus	Client::GetStatus() const				{ return (_status);	}

// Yeni eklenen metotların implementasyonu
bool Client::IsModeSet(char mode_char) const
{
	std::map<char, bool>::const_iterator it = _modes.find(mode_char);

	if (it != _modes.end())
	{
		return (it->second);
	}
	return (false);
}

std::string Client::GetModeString() const
{
	std::string mode_str = "+";

	if (IsModeSet('i')) mode_str += "i";
	if (IsModeSet('w')) mode_str += "w";
	if (IsModeSet('o')) mode_str += "o";
	
	if (mode_str == "+")
	{
		return "";
	}
	return mode_str;
}

void Client::ApplyModes(Client* sender, const std::string& mode_string, Server& server)
{
	if (sender->GetFD() != GetFD())
	{
		server.SendsNumericReply(sender, 502, ":Cant change mode for other users");
		return ;
	}
	
	char sign = '+';

	for (size_t i = 0; i < mode_string.length(); ++i)
	{
		char mode_char = mode_string[i];

		if (mode_char == '+' || mode_char == '-')
		{
			sign = mode_char;
			continue ;
		}

		switch (mode_char)
		{
			case 'i': handleInvisibleMode(sign, server); break;

			case 'w': handleWallopsMode(sign, server); break;

			case 'o':
				// Kullanıcılar kendi operatör modlarını değiştiremez.
				server.SendsNumericReply(sender, 481, ":Permission Denied - You're not an IRC operator");
				break;
			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode_char) + " :is unknown mode char to me");
				break;
		}
	}
}

// Yardımcı metotların implementasyonu
void Client::handleInvisibleMode(char sign, Server& server)
{
	bool current_status = IsModeSet('i');
	bool new_status = (sign == '+');
	
	if (current_status != new_status)
	{
		_modes['i'] = new_status;
		server.SendsNumericReply(this, 0, ":MODE " + GetNickName() + " " + std::string(1, sign) + "i");
	}
}

void Client::handleWallopsMode(char sign, Server& server)
{
	bool current_status = IsModeSet('w');
	bool new_status = (sign == '+');

	if (current_status != new_status)
	{
		_modes['w'] = new_status;
		server.SendsNumericReply(this, 0, ":MODE " + GetNickName() + " " + std::string(1, sign) + "w");
	}
}
