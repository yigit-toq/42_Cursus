/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:47 by ytop              #+#    #+#             */
/*   Updated: 2025/06/20 15:57:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <iostream>

User::User(int fd) : _fd(fd), _isAuthenticated(false) {}

User::~User() {}

int User::GetFd() const { return _fd; }

std::string User::GetNickname() const { return _nickname; }

std::string User::GetUsername() const { return _username; }

std::string User::GetRealname() const { return _realname; }

std::string User::GetHostname() const { return _hostname; }

bool User::IsAuthenticated() const { return _isAuthenticated; }

std::string User::GetInputBuffer() const { return _input_buffer; }

std::string User::GetOutputBuffer() const { return _output_buffer; }

void User::SetFd(int fd) { _fd = fd; }

void User::SetNickname(const std::string &nickname) { _nickname = nickname; }

void User::SetUsername(const std::string &username) { _username = username; }

void User::SetRealname(const std::string &realname) { _realname = realname; }

void User::SetHostname(const std::string &hostname) { _hostname = hostname; }

void User::SetAuthenticated(bool authenticated) { _isAuthenticated = authenticated; }



