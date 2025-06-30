/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:27 by ytop              #+#    #+#             */
/*   Updated: 2025/06/30 16:41:15 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client:: Client	(int fd) : _fd(fd), _isAuthenticated(false) {}

Client::~Client	() {}

int		Client::GetFd() const { return _fd; }

void	Client::SetFd(int fd) { _fd = fd; }

std::string Client::GetNickName		() const { return _nickname; }

std::string Client::GetUserName		() const { return _username; }

std::string Client::GetRealName		() const { return _realname; }

std::string Client::GetHostName		() const { return _hostname; }

std::string Client::GetInputBuffer	() const { return _input_buffer; }

std::string Client::GetOtputBuffer	() const { return _otput_buffer; }


bool Client::IsAuthenticated		() const { return _isAuthenticated; }


void Client::SetNickName			(const std::string &nickname)	{ _nickname = nickname; }

void Client::SetUserName			(const std::string &username)	{ _username = username; }

void Client::SetRealName			(const std::string &realname)	{ _realname = realname; }

void Client::SetHostName			(const std::string &hostname)	{ _hostname = hostname; }


void Client::AppendToInputBuffer	(const std::string &data)		{ _input_buffer += data; }

void Client::AppendToOtputBuffer	(const std::string &data)		{ _otput_buffer += data; }

void Client::SetAuthenticated (bool authenticated) { _isAuthenticated = authenticated; }

void Client::ClearOutputBuffer()
{
	_otput_buffer.clear();
}

std::string Client::ExtractNextMessage()
{
	size_t		pos		= _input_buffer.find("\r\n");

	if (pos == std::string::npos)
		return ("");

	std::string	message	= _input_buffer.substr(0, pos);

	_input_buffer.erase(0, pos + 1);

	return (message);
}
