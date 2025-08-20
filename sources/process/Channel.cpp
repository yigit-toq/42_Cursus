/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/08/17 01:21:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"

Channel:: Channel(const std::string& name, Server& server) : _name(name), _pass(""), _topic(""), _user_limit(0), _server(server)
{
	_modes['i'] = false;
	_modes['t'] = false;

	Logger::getInstance().Log(INFO, "Channel " + _name + " created.");
}

Channel::~Channel()
{
	Logger::getInstance().Log(INFO, "Channel " + _name + " destroyed.");
}

//--------------------   Getter Methods   --------------------

const std::string&				Channel::GetName		() const { return _name;	}
const std::string&				Channel::GetPass		() const { return _pass;	}
const std::string&				Channel::GetTopic		() const { return _topic;	}

const std::map<int, Client*>&	Channel::GetUsers		() const { return _users;		}
const std::map<int, Client*>&	Channel::GetOperators	() const { return _operators;	}

bool	Channel::IsUser		(Client* user) const
{
	if (!user) return (false);

	return (_users.		count(user->GetFD()) > 0);
}

bool	Channel::IsOperator	(Client* user) const
{
	if (!user) return (false);

	return (_operators.	count(user->GetFD()) > 0);
}

//------------------------------------------------------------

//--------------------   Setter Methods   --------------------

void	Channel::SetPass		(const std::string& pass)
{
	_pass = pass;

	Logger::getInstance().Log(INFO, "Channel " + _name + " pass set to: '" + _pass + "'");
}

void	Channel::SetName		(const std::string& name)
{
	_name = name;

	Logger::getInstance().Log(INFO, "Channel " + _name + " name set to: '" + _name + "'");
}

void	Channel::SetTopic		(const std::string& topic, Client* setter)
{
	_topic = topic;

	std::cout << "Channel " << _name << " topic set to: '" << _topic << "'";

	if (setter)
	{
		std::cout << " by " << setter->GetNickname();
	}

	std::cout << std::endl;
}

//------------------------------------------------------------

//--------------------  User  Management  --------------------

void	Channel::AddClient(Client* user)
{
	if (!user || IsUser(user))
	{
		return ;
	}

	_users[user->GetFD()] = user;

	if (_users.size() == 1)
	{
		AddOperator(user);
	}

	Logger::getInstance().Log(INFO, "User " + user->GetNickname() + " added to channel " + _name);
}

void	Channel::RmvClient(Client* user)
{
	if (!user || !IsUser(user))
	{
		return ;
	}

	RmvOperator		(user);

	_users.erase	(user->GetFD());

	Logger::getInstance().Log(INFO, "User " + user->GetNickname() + " removed from channel " + _name);
}

void	Channel::AddOperator(Client* user)
{
	if (!user || !IsUser(user) || IsOperator(user))
	{
		return ;
	}

	_operators[user->GetFD()] = user;

	Logger::getInstance().Log(INFO, "User " + user->GetNickname() + " is now an operator in channel " + _name);
}

void	Channel::RmvOperator(Client* user)
{
	if (!user || !IsOperator(user))
	{
		return ;
	}

	_operators.erase(user->GetFD());

	Logger::getInstance().Log(INFO, "User " + user->GetNickname() + " removed as operator from channel " + _name);
}

//------------------------------------------------------------

void	Channel::BroadcastMessage(const std::string& message, Client* exclude_user)
{
	for (std::map<int, Client*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		Client* target_user = it->second;

		if (target_user != exclude_user)
		{
			target_user->AppendToOuputBuffer	(message + "\r\n");

			_server.GetPollHandler().SetEvents	(target_user->GetFD(), POLLIN | POLLOUT);
		}
	}
	Logger::getInstance().Log(INFO, "Broadcasted message to channel " + _name + ": [" + message + "]");
}

bool	Channel::IsFull		()			const
{
	return (_user_limit > 0 && (int)_users.size() >= _user_limit);
}

bool	Channel::IsEmpty	()			const
{
	return (_users.empty ());
}

bool	Channel::IsModeSet	(char mode)	const
{
	std::map<char, bool>::const_iterator it = _modes.find(mode);

	if (it != _modes.end ())
	{
		return (it->second);
	}

	return (false);
}

//--------------------  Mode Management   --------------------

std::string	Channel::GetModeString() const
{
	std::string	mode = "+";

	if (IsModeSet('i')	) mode += "i";
	if (IsModeSet('t')	) mode += "t";

	if (!_pass.empty()	) mode += "k";

	if (_user_limit > 0	) mode += "l";

	if (mode == "+"		) return ("");

	return (mode);
}

std::string	Channel::GetModeParams() const
{
	std::string	params = "";

	if (IsModeSet('k')) params += _pass;

	if (_user_limit > 0)
	{
		std::stringstream	ss	;

		ss << _user_limit;

		params += " " + ss.str();
	}
	return (params);
}

void	Channel::ApplyModes(Client* sender, const std::string& mode_strs, const std::vector<std::string>& mode_args, Server& server)
{
	if (!IsOperator(sender))
	{
		server.SendsNumericReply(sender, 482, _name + " :You're not channel operator");
		return ;
	}

	char	sign = 0;

	std::vector<std::string>::const_iterator arg_it = mode_args.begin();

	for (size_t i = 0; i < mode_strs.length(); ++i)
	{
		char mode = mode_strs[i];

		if (mode == '+' || mode == '-')
		{
			sign =  mode;
			continue ;
		}
		if (sign == 0)
		{
			server.SendsNumericReply(sender, 472, std::string(1, mode) + " :unknown mod character");
			return ;
		}

		switch (mode)
		{
			case 'i':
				handle_I_Mode		(sender, sign);
				break ;

			case 't':
				handle_T_Mode		(sender, sign);
				break ;

			case 'k':
				if (arg_it != mode_args.end())
				{
					handle_K_Mode	(sender, sign, *(arg_it++));
				}
				else
				{
					handle_K_Mode	(sender, sign, "");
				}
				break ;

			case 'l':
				if (arg_it != mode_args.end())
				{
					handle_L_Mode	(sender, sign, *(arg_it++));
				}
				else
				{
					handle_L_Mode	(sender, sign, "");
				}
				break ;

			case 'o':
				if (arg_it != mode_args.end())
				{
					handle_O_Mode	(sender, sign, *(arg_it++));
				}
				break ;

			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode) + " :unknown mod character");
				break ;
		}

		if (Utils::IsModeWithParameter	(mode))
		{
			if (arg_it == mode_args.end())
			{
				server.SendsNumericReply(sender, 461, "MODE " + _name + " :Not enough parameters for mode " + std::string(1, mode));
			}
		}
	}
}

void	Channel::handle_I_Mode	(Client* sender, char sign)
{
	bool cur_status = IsModeSet('i');
	bool new_status = (sign ==  '+');

	if (cur_status != new_status)
	{
		_modes['i'] = new_status;

		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " " + std::string(1, sign) + "i");
	}
}

void	Channel::handle_T_Mode	(Client* sender, char sign)
{
	bool cur_status = IsModeSet('t');
	bool new_status = (sign ==  '+');

	if (cur_status != new_status)
	{
		_modes['t']	= new_status;

		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " " + std::string(1, sign) + "t");
	}
}

void	Channel::handle_K_Mode	(Client* sender, char sign, const std::string& param)
{
	if (sign == '+')
	{
		if (param.empty())
		{
			return ;
		}

		_pass = param	;

		_modes['k'] = 1	;

		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " +k " + _pass	);

		return ;
	}
	if (sign == '-')
	{
		_pass = ""		;

		_modes['k'] = 0	;

		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " -k "			);

		return ;
	}
}

void	Channel::handle_O_Mode	(Client* sender, char sign, const std::string& param)
{
	Client* target_user = _server.FindClient(param);

	if (!target_user)
	{
		_server.SendsNumericReply(sender, 401, param + " :No such nick");
		return ;
	}

	if (sign == '+')
	{
		if (IsOperator	(target_user) == 0)
		{
			AddOperator	(target_user);

			_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " +o " + target_user->GetNickname());
		}
		return ;
	}
	if (sign == '-')
	{
		if (IsOperator	(target_user) != 0)
		{
			RmvOperator	(target_user);

			_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " -o " + target_user->GetNickname());
		}
		return ;
	}
}

void	Channel::handle_L_Mode	(Client* sender, char sign, const std::string& param)
{
	if (sign == '+')
	{
		std::istringstream	iss(param)	;

		int					limit =  0	;

		if (!(iss >> limit) || limit <= 0)
		{
			_server.SendsNumericReply		(sender, 461 , "MODE " + _name + " :Invalid limit parameter");
		}
		else
		{
			_user_limit = limit	;

			_modes['l'] = 1		;

			_server.BroadcastChannelMessage	(this, sender, "MODE " + _name + " +l " + param);
		}
		return ;
	}
	if (sign == '-')
	{
			_user_limit = 0	;

			_modes['l'] = 0	;

			_server.BroadcastChannelMessage	(this, sender, "MODE " + _name + " -l");
	}
}

//------------------------------------------------------------

void	Channel::AddInvitedUser(const std::string& nickname)
{
	_invited_users.push_back(nickname);
}

void	Channel::RmvInvitedUser(const std::string& nickname)
{
	_invited_users.erase(std::remove(_invited_users.begin(), _invited_users.end(), nickname), _invited_users.end());
}

bool	Channel::IsUserInvited(const std::string& nickname) const
{
	return std::find(_invited_users.begin(), _invited_users.end(), nickname) != _invited_users.end();
}
