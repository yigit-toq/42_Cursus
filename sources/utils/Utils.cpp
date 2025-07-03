/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:54:05 by ytop              #+#    #+#             */
/*   Updated: 2025/07/03 15:10:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

Utils:: Utils() {}

Utils::~Utils() {}

std::string					Utils::trim (const std::string& str)
{
	size_t	first	= str.find_first_not_of	(" \t\n\r\f\v");

	if (std::string::npos == first)
		return ("");

	size_t	last	= str.find_last_not_of	(" \t\n\r\f\v");

	return (str.substr(first, (last - first + 1)));
}

std::vector<std::string>	Utils::split(const std::string& str, char delimiter)
{
	std::vector<std::string>	tokens;
	std::string					token;

	std::string::size_type		bgn	= 0;
	std::string::size_type		end	= str.find(delimiter);

	while (end != std::string::npos)
	{
		token	= str.substr(bgn, end - bgn);

		bgn		= end + 1;
		end		= str.find	(delimiter, bgn);

		tokens.push_back(token);
	}

	tokens.push_back(str.substr(bgn));

	return (tokens);
}
