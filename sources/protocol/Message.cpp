/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:53:21 by ytop              #+#    #+#             */
/*   Updated: 2025/07/02 18:37:43 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message:: Message() {}

Message::~Message() {}

const std::string&					Message::getPrefix		() const { return _prefix;		}
const std::string&					Message::getCommand		() const { return _command;		}
const std::vector<std::string>&		Message::getParameters	() const { return _parameters;	}

bool Message::parse(const std::string& raw_message)
{
	_prefix		.clear();
	_command	.clear();
	_parameters	.clear();

	if (raw_message.length() < 2 || raw_message.substr(raw_message.length() - 2) != "\r\n")
	{
		std::cerr << "Error: Message does not end with CRLF." << std::endl;

		return (false);
	}

	std::string				msg_content		= raw_message.substr(0, raw_message.length() - 2);

    std::string::size_type	current_pos		= 0;

	if (msg_content[0] == ':')
	{
		std::string::size_type space_pos	= msg_content.find(' ', 1);

		if (space_pos == std::string::npos)
		{
			std::cerr << "Error: Prefix found but no command." << std::endl;

			return (false);
		}

		_prefix		= msg_content.substr(1, space_pos - 1);

		current_pos	= space_pos + 1;
	}

	std::string::size_type	command_end_pos = msg_content.find(' ', current_pos);

	if (command_end_pos == std::string::npos)
	{
		_command	 = msg_content.substr(current_pos);

		std::transform(_command.begin(), _command.end(), _command.begin(), ::toupper);

		return (true);
	}
	else
	{
		_command	 = msg_content.substr(current_pos, command_end_pos - current_pos);

		std::transform(_command.begin(), _command.end(), _command.begin(), ::toupper);

		current_pos	 = command_end_pos + 1;
	}

	while (current_pos < msg_content.length())
	{
		if (msg_content[current_pos] == ':')
		{
			_parameters.push_back(msg_content.substr(current_pos + 1));

			break ;
		}
		else
		{
			std::string::size_type next_space = msg_content.find(' ', current_pos);

			if (next_space == std::string::npos)
			{
				_parameters.push_back(msg_content.substr(current_pos));

				break ;
			}
			else
			{
				_parameters.push_back(msg_content.substr(current_pos, next_space - current_pos));

				current_pos = next_space + 1;
			}
		}
	}
	return (true);
}

void	Message::print() const
{
	std::cout << "--- Message ---" << std::endl;

	if (!_prefix.empty())
	{
		std::cout << "Prefix: [" << _prefix << "]" << std::endl;
	}

	std::cout << "Command:		[" << _command				<< "]"	<< std::endl;
	std::cout << "Parameters	(" << _parameters.size()	<< "):"	<< std::endl;

	for (size_t i = 0; i < _parameters.size(); ++i)
	{
		std::cout << "  [" << _parameters[i] << "]" << std::endl;
	}

	std::cout << "---------------" << std::endl;
}
