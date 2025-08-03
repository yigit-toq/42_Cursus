/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/08/03 23:43:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include "Server.hpp"
#include "Client.hpp"

Channel:: Channel(const std::string& name, Server& server) : _name(name), _pass(""), _topic(""), _user_limit(0), _server(server), _creation_time(time(NULL))
{
	_modes['i'] = false;
	_modes['t'] = false;


	std::cout << "Channel " << _name << " created.	"	<< std::endl;
}

// Channel kapanınca seg alıyorum

Channel::~Channel()
{
	std::cout << "Channel " << _name << " destroyed."	<< std::endl;
}

const std::string&	Channel::GetName		() const { return _name;	}
const std::string&	Channel::GetPass		() const { return _pass;	}
const std::string&	Channel::GetTopic		() const { return _topic;	}

size_t				Channel::GetUserLimit	() const { return _user_limit;		}

bool 				Channel::IsInviteOnly	() const { return _invite_only;		}

bool 				Channel::IsTopicSetByOp	() const { return _topic_set_by_op;	}

bool	Channel::IsOperator	(Client* user) const
{
	if (!user) return (false);

	return (_operators.count(user->GetFD()) > 0);
}

bool	Channel::IsUser		(Client* user) const
{
	if (!user) return (false);

	return (_clients.count(user->GetFD()) > 0);
}

const std::map<int, Client*>& Channel::getUsers		() const { return _clients;		}
const std::map<int, Client*>& Channel::getOperators	() const { return _operators;	}

void	Channel::SetPass(const std::string& pass)
{
	_pass = pass;

	std::cout << "Channel " << _name << " password set." << std::endl;
}

void	Channel::SetTopic	(const std::string& topic, Client* setter)
{
	_topic = topic;

	std::cout << "Channel " << _name << " topic set to: '"	<< _topic << "'";

	if (setter)
	{
		std::cout << " by " << setter->GetNickName();
	}

	std::cout << std::endl;
}

void	Channel::SetUserLimit		(size_t limit)
{
	_user_limit = limit;

	std::cout << "Channel " << _name << " user limit set to: "				<< _user_limit << std::endl;
}

void	Channel::SetInviteOnly		(bool status)
{
	_invite_only = status;

	std::cout << "Channel " << _name << " invite-only status set to: "		<< (status ? "true" : "false") << std::endl;
}

void	Channel::SetTopicSetByOp	(bool status)
{
	_topic_set_by_op = status;

	std::cout << "Channel " << _name << " topic-set-by-op status set to: "	<< (status ? "true" : "false") << std::endl;
}

void	Channel::AddClient(Client* user)
{
	if (!user || IsUser(user))
	{
		return ;
	}
	_clients[user->GetFD()] = user;

	if (_clients.size() == 1)
	{
		AddOperator(user);
	}

	std::cout << "User " << user->GetNickName() << " added to channel "		<< _name << std::endl;
}

void	Channel::RmvClient(Client* user)
{
	if (!user || !IsUser(user))
	{
		return ;
	}
	RmvOperator		(user);

	_clients.erase	(user->GetFD());

	std::cout << "User " << user->GetNickName() << " removed from channel " << _name << std::endl;
}

void	Channel::AddOperator(Client* user)
{
	if (!user || !IsUser(user) || IsOperator(user))
	{
		return ;
	}
	_operators[user->GetFD()] = user;

	std::cout << "User " << user->GetNickName() << " is now an operator in "		<< _name << std::endl;
}

void	Channel::RmvOperator(Client* user)
{
	if (!user || !IsOperator(user))
	{
		return ;
	}
	_operators.erase(user->GetFD());

	std::cout << "User " << user->GetNickName() << " is no longer an operator in "	<< _name << std::endl;
}

void	Channel::BroadcastMessage(const std::string& message, Client* exclude_user)
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
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

bool	Channel::IsFull	() const
{
	return (_user_limit > 0 && _clients.size() >= _user_limit);
}

bool	Channel::IsEmpty() const
{
	return (_clients.empty());
}

bool	Channel::IsChannelModeWithParameter(char mode_char)
{
	return (mode_char == 'o' || mode_char == 'l' || mode_char == 'k');
}


bool Channel::IsModeSet(char mode_char) const //
{
	std::map<char, bool>::const_iterator it = _modes.find(mode_char);

	if (it != _modes.end())
	{
		return (it->second);
	}
	return (false);
}

std::string Channel::GetModeString() const //
{
	std::string mode_str = "+";

	if (IsModeSet('i')) mode_str += "i";
	if (IsModeSet('t')) mode_str += "t";
	if (!_pass.empty()) mode_str += "k";

	if (_user_limit > 0) mode_str += "l";

	if (mode_str == "+") return "";

	return (mode_str);
}

std::string Channel::GetModeParams() const //
{
	std::string params = "";

	if (IsModeSet('k')) params += " " + _pass;

	if (_user_limit > 0)
	{
		std::stringstream ss;

		ss << _user_limit;
		params += " " + ss.str();
	}
	return (params);
}

// ApplyModes metodu: Modları ayrıştırır ve her birini işler
void Channel::ApplyModes(Client* sender, const std::string& mode_string, const std::vector<std::string>& mode_args, Server& server)
{
	if (!IsOperator(sender))
	{
		server.SendsNumericReply(sender, 482, _name + " :You're not channel operator");
		return;
	}

	char sign = '+';
	std::vector<std::string>::const_iterator arg_it = mode_args.begin();

	for (size_t i = 0; i < mode_string.length(); ++i)
	{
		char mode_char = mode_string[i];

		if (mode_char == '+' || mode_char == '-')
		{
			sign = mode_char;
			continue;
		}

		switch (mode_char)
		{
			case 'i': handleInviteOnlyMode(sender, sign); break;

			case 't': handleTopicMode(sender, sign); break;

			case 'k':
				if (arg_it != mode_args.end())
				{
					handleKeyMode(sender, sign, *(arg_it++));
				} else {
					server.SendsNumericReply(sender, 461, "MODE " + _name + " :Not enough parameters for mode +k");
				}
				break;

			case 'o':
				if (arg_it != mode_args.end())
				{
					handleOperatorMode(sender, sign, *(arg_it++));
				} else {
					server.SendsNumericReply(sender, 461, "MODE " + _name + " :Not enough parameters for mode +o");
				}
				break;

			case 'l':
				if (arg_it != mode_args.end())
				{
					handleLimitMode(sender, sign, *(arg_it++));
				} else {
					server.SendsNumericReply(sender, 461, "MODE " + _name + " :Not enough parameters for mode +l");
				}
				break;

			default:
				server.SendsNumericReply(sender, 472, std::string(1, mode_char) + " :is unknown mode char to me");
				break;
		}
	}
}

// Her mod için özel işleyici metotlar
void Channel::handleInviteOnlyMode(Client* sender, char sign)
{
	bool current_status = IsModeSet('i');
	bool new_status = (sign == '+');

	if (current_status != new_status)
	{
		_modes['i'] = new_status;
		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " " + std::string(1, sign) + "i");
	}
}

void Channel::handleTopicMode(Client* sender, char sign)
{
	bool current_status = IsModeSet('t');
	bool new_status = (sign == '+');

	if (current_status != new_status)
	{
		_modes['t'] = new_status;
		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " " + std::string(1, sign) + "t");
	}
}

void Channel::handleKeyMode(Client* sender, char sign, const std::string& param)
{
	if (sign == '+')
	{
		_pass = param;
		_modes['k'] = true;
		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " +k " + _pass);
	}
	else if (sign == '-')
	{
		_pass = "";
		_modes['k'] = false;
		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " -k");
	}
}

void Channel::handleOperatorMode(Client* sender, char sign, const std::string& param)
{
	Client* target_user = _server.FindClient(param);

	if (!target_user)
	{
		_server.SendsNumericReply(sender, 401, param + " :No such nick");
		return;
	}

	if (sign == '+')
	{
		if (!IsOperator(target_user))
		{
			AddOperator(target_user);
			_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " +o " + target_user->GetNickName());
		}
	}
	else if (sign == '-')
	{
		if (IsOperator(target_user))
		{
			RmvOperator(target_user);
			_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " -o " + target_user->GetNickName());
		}
	}
}

void Channel::handleLimitMode(Client* sender, char sign, const std::string& param)
{
	if (sign == '+')
	{
		std::istringstream iss(param);
		size_t limit;
		if (iss >> limit)
		{
			_user_limit = limit;
			_modes['l'] = true;
			_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " +l " + param);
		}
		else
		{
			_server.SendsNumericReply(sender, 461, "MODE " + _name + " :Invalid limit parameter");
		}
	}
	else if (sign == '-')
	{
		_user_limit = 0;
		_modes['l'] = false;
		_server.BroadcastChannelMessage(this, sender, "MODE " + _name + " -l");
	}
}
