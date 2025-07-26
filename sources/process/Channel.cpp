/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/07/26 05:28:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include "Server.hpp"
#include "Client.hpp"

Channel:: Channel(const std::string& name, Server& server) : _name(name), _pass(""), _topic(""), _user_limit(0), _server(server), _creation_time(time(NULL))
{
	_modes['i'] = false;
	_modes['t'] = false;

	_mode_handlers['i'] = [this](Client* sender, char sign, const std::string& param, bool& changed, Server& server)
	{
		(void)param;

		bool current_status = IsModeSet('i');

		if (sign == '+' && !current_status)
		{
			SetMode('i', true);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " +i :Channel is now invite-only.");
		}
		else if (sign == '-' && current_status)
		{
			SetMode('i', false);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " -i :Channel is no longer invite-only.");
		}
	};

	_mode_handlers['t'] = [this](Client* sender, char sign, const std::string& param, bool& changed, Server& server)
	{
		(void)param;

		bool current_status = IsModeSet('t');

		if (sign == '+' && !current_status)
		{
			SetMode('t', true);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " +t :Topic can now only be set by operators.");
		}
		else if (sign == '-' && current_status)
		{
			SetMode('t', false);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " -t :Topic can now be set by anyone.");
		}
	};

	_mode_handlers['k'] = [this](Client* sender, char sign, const std::string& param, bool& changed, Server& server)
	{
		if (sign == '+')
		{
			if (!_pass.empty())
			{
				server.SendsNumericReply(sender, 467, _name + " :Channel key already set"); // ERR_KEYSET (467)
				return;
			}
			SetPass(param);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " +k " + param + " :Channel key set.");
		}
		else if (sign == '-')
		{
			if (_pass.empty())
			{
				return;
			}
			SetPass("");
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " -k :Channel key removed.");
		}
	};

	_mode_handlers['o'] = [this](Client* sender, char sign, const std::string& param, bool& changed, Server& server)
	{
		if (param.empty())
		{
			server.SendsNumericReply(sender, 461, "MODE " + _name + " " + sign + "o :Not enough parameters");
			return;
		}
		Client* target_user = server.FindClient(param);
		if (!target_user || !IsUser(target_user))
		{
			server.SendsNumericReply(sender, 401, param + " :No such nick/They aren't on that channel"); // ERR_NOSUCHNICK (401)
			return;
		}

		if (sign == '+')
		{
			if (!IsOperator(target_user))
			{
				AddOperator(target_user);
				changed = true;
				server.SendsNumericReply(sender, 0, _name + " +o " + target_user->GetNickName() + " :User is now a channel operator.");
			}
		}
		else if (sign == '-')
		{
			if (IsOperator(target_user))
			{
				// Not: Son operatörün kendisini deoperatör yapmasını engellemek için daha fazla kontrol eklenebilir.
				// Örneğin: if (_operators.size() == 1 && target_user->GetFD() == sender->GetFD()) { /* Hata */ }
				RmvOperator(target_user);
				changed = true;
				server.SendsNumericReply(sender, 0, _name + " -o " + target_user->GetNickName() + " :User is no longer a channel operator.");
			}
		}
	};

	_mode_handlers['l'] = [this](Client* sender, char sign, const std::string& param, bool& changed, Server& server)
	{
		if (sign == '+')
		{
			if (param.empty())
			{
				server.SendsNumericReply(sender, 461, "MODE " + _name + " +l :Not enough parameters");
				return;
			}
			std::istringstream iss(param);
			size_t limit;
			if (!(iss >> limit) || limit == 0)
			{
				server.SendsNumericReply(sender, 0, _name + " :Invalid limit value provided.");
				return;
			}
			SetUserLimit(limit);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " +l " + param + " :User limit set to " + param + ".");
		}
		else if (sign == '-')
		{
			if (_user_limit == 0)
			{
				return;
			}
			SetUserLimit(0);
			changed = true;
			server.SendsNumericReply(sender, 0, _name + " -l :User limit removed.");
		}
	};
	std::cout << "Channel " << _name << " created."		<< std::endl;
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

std::string Channel::GetModeString() const
{
	std::string mode_str = "+";
	if (IsModeSet('i')) mode_str += "i";
	if (IsModeSet('t')) mode_str += "t";
	if (!_pass.empty()) mode_str += "k";
	if (_user_limit > 0) mode_str += "l";

	if (mode_str == "+")
	{
		return "";
	}
	std::string sorted_modes = mode_str.substr(1);
	std::sort(sorted_modes.begin(), sorted_modes.end());
	return ("+" + sorted_modes);
}
