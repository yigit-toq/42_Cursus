/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 21:43:41 by ytop             ###   ########.fr       */
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


	std::cout << "Channel " << _name << " created.  "	<< std::endl;
}

Channel::~Channel()
{
	std::cout << "Channel " << _name << " destroyed."	<< std::endl;
}

//--------------------   Getter Methods   --------------------

const std::string&				Channel::GetName		() const { return _name;	}
const std::string&				Channel::GetPass		() const { return _pass;	}
const std::string&				Channel::GetTopic		() const { return _topic;	}

const std::map<int, Client*>&	Channel::GetUsers		() const { return _users;		}
const std::map<int, Client*>&	Channel::GetOperators	() const { return _operators;	}

size_t							Channel::GetUserLimit	() const { return _user_limit;	}

bool 							Channel::IsInviteOnly	() const { return _invite_only;	}
bool 							Channel::IsTopicSetOp	() const { return _topic_by_op;	}

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

void	Channel::SetName		(const std::string& name)
{
	_name = name;

	std::cout << "Channel " << _name << " name set." << std::endl;
}

void	Channel::SetPass		(const std::string& pass)
{
	_pass = pass;

	std::cout << "Channel " << _name << " pass set." << std::endl;
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

void	Channel::SetUserLimit	(size_t limit)
{
	_user_limit  = limit;

	std::cout << "Channel " << _name << " user             limit set to: "	<< _user_limit					<< std::endl;
}

void	Channel::SetInviteOnly	(bool status)
{
	_invite_only = status;

	std::cout << "Channel " << _name << " invite-only     status set to: "	<< (status ? "true" : "false")	<< std::endl;
}

void	Channel::SetTopicSetOp	(bool status)
{
	_topic_by_op = status;

	std::cout << "Channel " << _name << " topic-set-by-op status set to: "	<< (status ? "true" : "false")	<< std::endl;
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

	std::cout << "User " << user->GetNickname() << " added     to channel " << _name << std::endl;
}

void	Channel::RmvClient(Client* user)
{
	if (!user || !IsUser(user))
	{
		return ;
	}

	RmvOperator		(user);

	_users.erase	(user->GetFD());

	std::cout << "User " << user->GetNickname() << " removed from channel " << _name << std::endl;
}

void	Channel::AddOperator(Client* user)
{
	if (!user || !IsUser(user) || IsOperator(user))
	{
		return ;
	}

	_operators[user->GetFD()] = user;

	std::cout << "User " << user->GetNickname() << " is now       an operator in " << _name << std::endl;
}

void	Channel::RmvOperator(Client* user)
{
	if (!user || !IsOperator(user))
	{
		return ;
	}

	_operators.erase(user->GetFD());

	std::cout << "User " << user->GetNickname() << " is no longer an operator in " << _name << std::endl;
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
	std::cout << "Broadcasted message to channel " << _name << ": [" << message << "]" << std::endl;
}

bool	Channel::IsFull		()			const
{
	return (_user_limit > 0 && _users.size() >= _user_limit);
}

bool	Channel::IsEmpty	()			const
{
	return (_users.empty());
}

bool	Channel::IsModeSet	(char mode)	const
{
	std::map<char, bool>::const_iterator it = _modes.find(mode);

	if (it != _modes.end())
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

	if (IsModeSet('k')) params += " " + _pass;

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

	char	sign = '+';

	std::vector<std::string>::const_iterator arg_it = mode_args.begin();

	for (size_t i = 0; i < mode_strs.length(); ++i)
	{
		char mode_char = mode_strs[i];

		if (mode_char == '+' || mode_char == '-')
		{
			sign = mode_char;
			continue ;
		}

		switch (mode_char)
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
				break ;

			case 'l':
				if (arg_it != mode_args.end())
				{
					handle_L_Mode	(sender, sign, *(arg_it++));
				}
				break ;

			case 'o':
				if (arg_it != mode_args.end())
				{
					handle_O_Mode	(sender, sign, *(arg_it++));
				}
				break ;

			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode_char) + " :unknown mod character");
				break ;
		}

		if (Utils::IsModeWithParameter	(mode_char))
		{
			if (arg_it == mode_args.end())
			{
				server.SendsNumericReply(sender, 461, "MODE " + _name + " :Not enough parameters for mode " + std::string(1, mode_char));
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
		_modes['t'] = new_status;

		_topic_by_op = new_status; //

		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " " + std::string(1, sign) + "t");
	}
}

void	Channel::handle_K_Mode	(Client* sender, char sign, const std::string& param)
{
	if (sign == '+')
	{
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

		size_t				limit = 0	;

		if (iss >> limit)
		{
			_user_limit = limit	;

			_modes['l'] = 1		;

			_server.BroadcastChannelMessage	(this, sender, "MODE " + _name + " +l " + param);
		}
		else
		{
			_server.SendsNumericReply		(sender, 461 , "MODE " + _name + " :Invalid limit parameter");
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
