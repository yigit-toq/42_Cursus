/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:55 by ytop              #+#    #+#             */
/*   Updated: 2025/07/23 15:01:19 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include "Server.hpp"
#include "Client.hpp"

Channel:: Channel(const std::string& name, Server& server) : _name(name), _user_limit(0), _invite_only(false), _topic_set_by_op(false), _server(server)
{
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

	// TOPIC komutunu implemente ettiğimizde buraya broadcast eklenecek.
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

	std::cout << "User " << user->GetNickName() << " added to channel " << _name << std::endl;

	if (_clients.size() == 1)
	{
		AddOperator(user);
	}
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

	std::cout << "User " << user->GetNickName() << " is now an operator in " << _name << std::endl;
}

void	Channel::RmvOperator(Client* user)
{
	if (!user || !IsOperator(user))
	{
		return ;
	}
	_operators.erase(user->GetFD());

	std::cout << "User " << user->GetNickName() << " is no longer an operator in " << _name << std::endl;
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

bool	Channel::IsEmpty() const
{
	return (_clients.empty());
}

bool	Channel::IsFull	() const
{
	return (_user_limit > 0 && _clients.size() >= _user_limit);
}
