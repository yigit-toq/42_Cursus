/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:13:04 by ytop              #+#    #+#             */
/*   Updated: 2025/05/30 23:13:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(const int socket)
{
	_socket = socket;

	_username = "";
	_hostname = "";

	_isRegistered = false;

	std::cout << "Client created with socket: " << _socket << std::endl;
}
