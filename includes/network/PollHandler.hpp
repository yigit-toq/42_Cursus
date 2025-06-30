/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:51:02 by ytop              #+#    #+#             */
/*   Updated: 2025/06/30 16:07:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLHANDLER_HPP
#define POLLHANDLER_HPP

#pragma region header

#include <iostream>
#include <vector>
#include <cerrno>
#include <poll.h>

#pragma endregion

class PollHandler
{
	private:
		std::vector<struct pollfd>	_fds;

	public:
		 PollHandler	();

		~PollHandler	();

		void RmvSocket	(int fd);
		void AddSocket	(int fd, short events);

		std::vector<struct pollfd>	WaitForEvents(int timeout_ms = -1);
};

#endif
