/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:00:00 by ytop              #+#    #+#             */
/*   Updated: 2025/08/04 22:52:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollHandler.hpp"

PollHandler:: PollHandler() {}

PollHandler::~PollHandler() {}

//bakılacak

void	PollHandler::AddSocket(int fd, short events)
{
	struct pollfd	pollFD;

	pollFD.fd		= fd;
	pollFD.events	= events;

	_fds.push_back(pollFD);
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

			_fds[i].revents = 0;
		}
	}
	return (ready_fds);
}

void	PollHandler::SetEvents(int fd, short events)
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == fd)
		{
			_fds[i].events = events;

			std::cout << "Updated events for FD " << fd << " to " << events << std::endl;

			return ;
		}
	}
	std::cerr << "Warning: Attempted to set events for non-existent FD " << fd << std::endl;
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
