/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:00:00 by ytop              #+#    #+#             */
/*   Updated: 2025/06/24 19:00:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollHandler.hpp"
#include <iostream>
#include <algorithm>

PollHandler::PollHandler() {}
PollHandler::~PollHandler() {}

void PollHandler::addFd(int fd, short events) {
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = events;
	_fds.push_back(pfd);
}