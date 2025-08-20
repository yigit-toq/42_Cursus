/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/08/17 01:32:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

Client:: Client	(int fd) : _fd(fd), _status(UNREGISTERED), _connection_time(time(NULL))
{
	_nickname		= "*";
	_username		= "";
	_realname		= "";
	_hostname		= "";
	_password		= "";

	_modes['i']		= false;
	_modes['o']		= false;

	_authenticated	= false;

	Logger::getInstance().Log(INFO, "Client created with FD: " + ft_to_string(_fd));
}

Client::~Client	() {}

//--------------------   Getter Methods   --------------------

int			Client::GetFD						(void) const					{ return _fd; }

UserStatus	Client::GetStatus					() const						{ return (_status);	}

std::string Client::GetNickname					() const						{ return _nickname; }
std::string Client::GetUsername					() const						{ return _username; }
std::string Client::GetRealname					() const						{ return _realname; }
std::string Client::GetHostname					() const						{ return _hostname; }
std::string Client::GetPassword					() const						{ return _password; }

const std::string&				Client::GetOutputBuffer	() const
{
	return (_ouput_buffer	);
}

const std::vector<Channel*>&	Client::GetJoinChannels	() const
{
	return (_join_channels	);
}

//------------------------------------------------------------

//--------------------   Setter Methods   --------------------

void		Client::SetFD						(int fd)						{ _fd	= fd; }

void		Client::SetStatus					(UserStatus status)				{ _status = status;	}

void		Client::SetNickname					(const std::string &nickname)	{ _nickname = nickname; }
void		Client::SetUsername					(const std::string &username)	{ _username = username; }
void		Client::SetRealname					(const std::string &realname)	{ _realname = realname; }
void		Client::SetHostname					(const std::string &hostname)	{ _hostname = hostname; }
void		Client::SetPassword					(const std::string &password)	{ _password = password; }

//------------------------------------------------------------

//--------------------    Input/Output    --------------------

void	Client::AppendToInputBuffer	(const std::string &data)
{
	_input_buffer += data;
}

void	Client::AppendToOuputBuffer	(const std::string& data)
{
	_ouput_buffer.append(data);

	Logger::getInstance().Log(INFO, "User " + _nickname + " appended " + ft_to_string(data.length()) + " bytes to output buffer. Total size: " + ft_to_string(_ouput_buffer.length()));
}

void	Client::PopOutputBuffer		(size_t count)
{
	if (count <= _ouput_buffer.length())
	{
		_ouput_buffer.erase(0, count);

		Logger::getInstance().Log(INFO, "User " + _nickname + " popped " + ft_to_string(count) + " bytes from output buffer. Remaining size: " + ft_to_string(_ouput_buffer.length()));
	}
	else
	{
		_ouput_buffer.clear();

		Logger::getInstance().Log(INFO, "User " + _nickname + " output buffer cleared.");
	}
}

//------------------------------------------------------------

//--------------------  Register  Status  --------------------

bool	Client::IsRegistered() const
{
	return (_status == REGISTERED );
}

bool	Client::HasOuputData() const
{
	return (!_ouput_buffer.empty());
}

//------------------------------------------------------------

//-------------------- Channel Management --------------------

void	Client::AddChannel(Channel* channel)
{
	for (size_t i = 0; i < _join_channels.size(); ++i)
	{
		if (_join_channels[i] == channel)
			return ;
	}
	_join_channels.push_back(channel);

	Logger::getInstance().Log(INFO, "Client " + _nickname + " added to joined channel list: " + channel->GetName());
}

void	Client::RmvChannel(Channel* channel)
{
	for (std::vector<Channel*>::iterator it = _join_channels.begin(); it != _join_channels.end(); ++it)
	{
		if (*it == channel)
		{
			_join_channels.erase(it);

			Logger::getInstance().Log(INFO, "Client " + _nickname + " removed from joined channel list: " + channel->GetName());

			return ;
		}
	}
}

//------------------------------------------------------------

//--------------------   Mode  Handling   --------------------

void	Client::ApplyModes			(Client* sender, const std::string& mode_string, Server& server)
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
			case 'i':
				handle_I_Mode(sign, server);
				break ;

			case 'o':
				server.SendsNumericReply(sender, 481, ":Permission Denied - You're not an IRC operator"			);
				break ;

			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode_char) + " :is unknown mode char to me");
				break ;
		}
	}
}

void	Client::handle_I_Mode		(char sign, Server& server)
{
	bool cur_status = IsModeSet('i');
	bool new_status = (sign ==  '+');
	
	if (cur_status != new_status)
	{
		_modes['i'] = new_status;
		server.SendsNumericReply(this, 0, ":MODE " + GetNickname() + " " + std::string(1, sign) + "i");
	}
}

std::string	Client::GetModeString	() const
{
	std::string mode = "+";

	if (IsModeSet('i')) mode += "i";
	if (IsModeSet('o')) mode += "o";
	
	if (mode == "+")
	{
		return  ("");
	}
	return (mode);
}

bool		Client::IsModeSet		(char mode_char) const
{
	std::map<char, bool>::const_iterator it = _modes.find(mode_char);

	if (it != _modes.end())
	{
		return (it->second);
	}
	return (false);
}

//------------------------------------------------------------

std::string Client::ExtractNextMessage()
{
	size_t		pos		= _input_buffer.find	("\r\n");

	if (pos == std::string::npos)
		return ("");

	std::string	message	= _input_buffer.substr	(0, pos);

	_input_buffer.erase(0, pos + 2);

	return (message);
}

//------------------------------------------------------------
