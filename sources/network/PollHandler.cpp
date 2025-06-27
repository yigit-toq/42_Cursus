/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:00:00 by ytop              #+#    #+#             */
/*   Updated: 2025/06/27 17:00:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollHandler.hpp"

PollHandler::PollHandler() {}
PollHandler::~PollHandler() {}

void PollHandler::AddSocket(int fd, short events)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = events;
	_fds.push_back(pfd);
}

void PollHandler::RmvSocket(int fd)
{
    for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
        if (it->fd == fd) {
            _fds.erase(it);
            return;
        }
    }
}

std::vector<struct pollfd> PollHandler::WaitForEvents(int timeout_ms)
{
    std::vector<struct pollfd> ready_fds;
    int ret = poll(&_fds[0], _fds.size(), timeout_ms);

    if (ret == -1) {
        // Hata
        if (errno == EINTR) { // Sinyal tarafından kesildi
            return ready_fds;
        }
        throw std::runtime_error("Error in poll()");
    }

    if (ret == 0) {
        // Zaman aşımı, olay yok
        return ready_fds;
    }

    for (size_t i = 0; i < _fds.size(); ++i) {
        if (_fds[i].revents != 0) {
            ready_fds.push_back(_fds[i]);
            _fds[i].revents = 0;
        }
    }
    return ready_fds;
}
