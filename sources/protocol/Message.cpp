/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:53:21 by ytop              #+#    #+#             */
/*   Updated: 2025/08/10 06:03:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

#include "Utils.hpp"

Message:: Message() {}

Message::~Message() {}

const std::string&					Message::GetPrefix		() const { return _prefix;		}
const std::string&					Message::GetCommand		() const { return _command;		}
const std::vector<std::string>&		Message::GetParameters	() const { return _parameters;	}

bool Message::Parse(const std::string& raw_message)
{
	_prefix		.clear();
	_command	.clear();
	_parameters	.clear();

	std::string				ms_content	= raw_message;

	if (ms_content.empty())
	{
		return (false);
	}

	std::string::size_type	next_space	= 0;
	std::string::size_type	curr_posit	= 0;

	if (ms_content[0] == ':')
	{
		if ((next_space = ms_content.find(' ', 1)) == std::string::npos)
		{
			std::cerr << "Error: Malformed message with only prefix or empty command part." << std::endl;

			return (false);
		}

		_prefix		= ms_content.substr(1, next_space - 1);

		 curr_posit	= next_space + 1;
	}

	if ((curr_posit = ms_content.find_first_not_of(' ', curr_posit)) == std::string::npos)
	{
		std::cerr << "Error: No command found after prefix or leading spaces." << std::endl;

		return (false);
	}

	next_space		= ms_content.find(' ',	curr_posit);

	if (next_space == std::string::npos)
	{
		_command	= ms_content.substr(	curr_posit);
	}
	else
	{
		_command	= ms_content.substr(	curr_posit, next_space - curr_posit);

		curr_posit	= next_space + 1;
	}

	std::transform(_command.begin(), _command.end(), _command.begin(), ::toupper);

	curr_posit		= ms_content.find_first_not_of(' ', curr_posit);

	if (curr_posit != std::string::npos && curr_posit < ms_content.length())
	{
		if (ms_content[curr_posit] == ':')
		{
			_parameters.push_back(ms_content.substr(curr_posit + 1));
		}
		else
		{
			std::string				remaning_param_str	= ms_content.substr(curr_posit);

			std::string::size_type	trailing_colon_pos	= remaning_param_str.find(':');

			if (trailing_colon_pos != std::string::npos)
			{
				std::string					non_tr_part			= remaning_param_str.substr(0, trailing_colon_pos);

				std::vector<std::string>	temp_params			= Utils::split(non_tr_part, ' ');

				for (size_t i = 0; i < temp_params.size(); ++i)
				{
					std::string trimmed_param = Utils::trim(temp_params[i]);

					if (!trimmed_param.empty ())
					{
						_parameters.push_back(trimmed_param);
					}
				}

				_parameters.push_back(remaning_param_str.substr(trailing_colon_pos + 1));
			}
			else
			{
				std::vector<std::string>	temp_params = Utils::split(remaning_param_str, ' ');

				for (size_t i = 0; i <		temp_params.size(); ++i)
				{
					std::string trimmed_param = Utils::trim(temp_params[i]);

					if (!trimmed_param.empty ())
					{
						_parameters.push_back(trimmed_param);
					}
				}
			}
		}
	}

	return (true);
}

void	Message::Print() const
{
	std::cout << "--- Message ---" << std::endl;

	if (!_prefix.empty())
	{
		std::cout << "Prefix: [" << _prefix << "]" << std::endl;
	}

	std::cout << "Command:\n[" << _command				<< "]"	<< std::endl;
	std::cout << "Parameters(" << _parameters.size()	<< "):"	<< std::endl;

	for (size_t i = 0; i  < _parameters.size(); ++i)
	{
		std::cout << "[" << _parameters[i] << "]" << std::endl;
	}

	std::cout << "---------------" << std::endl;
}
