/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:12:03 by ytop              #+#    #+#             */
/*   Updated: 2025/05/30 23:12:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	private:
		int			_socket;

		std::string	_username;
		std::string	_hostname;

		bool		_isRegistered;

	public:
		Client (const int socket);

};

#endif
