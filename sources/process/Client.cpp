/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/08/05 21:17:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

//bakılacak

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

std::string Client::GetNickname					() const { return _nickname; }
std::string Client::GetUsername					() const { return _username; }
std::string Client::GetRealname					() const { return _realname; }
std::string Client::GetHostname					() const { return _hostname; }
std::string Client::GetPassword					() const { return _password; }

void	Client::SetNickname						(const std::string &nickname)	{ _nickname = nickname; }
void	Client::SetUsername						(const std::string &username)	{ _username = username; }
void	Client::SetRealname						(const std::string &realname)	{ _realname = realname; }
void	Client::SetHostname						(const std::string &hostname)	{ _hostname = hostname; }
void	Client::SetPassword						(const std::string &password)	{ _password = password; }

void	Client::AppendToInputBuffer				(const std::string &data)		{ _input_buffer += data; }

void	Client::AppendToOuputBuffer				(const std::string& data)
{
	_ouput_buffer.append(data);

	std::cout << "User " << GetNickname() << " appended " << data.length() << " bytes to output buffer. Total size: " << _ouput_buffer.length() << std::endl;
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

		std::cout << "User " << GetNickname() << " popped " << count << " bytes from output buffer. Remaining: " << _ouput_buffer.length() << std::endl;
	}
	else
	{
		_ouput_buffer.clear();

		std::cout << "User " << GetNickname() << " output buffer cleared." << std::endl;
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
			case 'i': handle_I_Mode(sign, server); break;

			case 'w': handle_W_Mode(sign, server); break;

			case 'o':
				server.SendsNumericReply(sender, 481, ":Permission Denied - You're not an IRC operator"			);
				break;

			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode_char) + " :is unknown mode char to me");
				break;
		}
	}
}

void Client::handle_I_Mode(char sign, Server& server)
{
	bool cur_status = IsModeSet('i');
	bool new_status = (sign ==  '+');
	
	if (cur_status != new_status)
	{
		_modes['i'] = new_status;
		server.SendsNumericReply(this, 0, ":MODE " + GetNickname() + " " + std::string(1, sign) + "i");
	}
}

void Client::handle_W_Mode(char sign, Server& server)
{
	bool cur_status = IsModeSet('w');
	bool new_status = (sign ==  '+');

	if (cur_status != new_status)
	{
		_modes['w'] = new_status;
		server.SendsNumericReply(this, 0, ":MODE " + GetNickname() + " " + std::string(1, sign) + "w");
	}
}
