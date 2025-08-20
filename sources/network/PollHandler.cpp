/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:00:00 by ytop              #+#    #+#             */
/*   Updated: 2025/08/06 23:48:31 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollHandler.hpp"

PollHandler:: PollHandler() {}

PollHandler::~PollHandler() {}

void	PollHandler::AddSocket(int fd, short events)
{
	struct pollfd	pollFD;

	pollFD.fd		= fd;
	pollFD.events	= events;

	_fds.push_back	(pollFD);
}

void	PollHandler::RmvSocket(int fd)
{
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == fd)
		{
			_fds.erase(it);
			return ;
		}
	}
}

void	PollHandler::SetEvents(int fd, short events)
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == fd)
		{
			_fds[i].events = events;

			Logger::getInstance().Log(INFO, "Updated events for FD " + ft_to_string(fd) + " to " + ft_to_string(events));

			return ;
		}
	}
	Logger::getInstance().Log(WARNING, "Attempted to set events for non-existent FD " + ft_to_string(fd));
}

short	PollHandler::GetEvents(int fd) const
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == fd)
		{
			return (_fds[i].events);
		}
	}
	return (0);
}

std::vector<struct pollfd>	PollHandler::WaitForEvents(int timeout_ms)
{
	std::vector<struct pollfd>	ready_fds;

	int	ret = poll(&_fds[0], _fds.size(), timeout_ms);

	if (ret == -1)
	{
		if (errno == EINTR)
			return (ready_fds);

		throw std::runtime_error("Error in poll()");
	}

	if (ret == 0)
		return (ready_fds);

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].revents != 0)
		{
			ready_fds.push_back(_fds[i]);

			_fds[i].revents  = 0;
		}
	}
	return (ready_fds);
}
