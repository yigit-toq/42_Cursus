/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:53:54 by ytop              #+#    #+#             */
/*   Updated: 2025/08/12 17:19:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

#include <ctime>

Logger:: Logger() {}

Logger::~Logger() {}

typedef struct tm tm;

void	Logger::Log(LogLevel level, const std::string& message)
{
	std::string	level_str;

	char		timestamp_str[80];

	switch (level)
	{
		case INFO:
			level_str = "[INFO]"	;
			break ;

		case DEBUG:
			level_str = "[DEBUG]"	;
			break ;

		case ERROR:
			level_str = "[ERROR]"	;
			break ;

		case WARNING:
			level_str = "[WARNING]"	;
			break ;
	}

	time_t	 now = time			(0);

	tm*		 ltm = localtime	(&now);

	strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", ltm);

	std::ostream&	output = (level == ERROR) ? std::cerr : std::cout;

	output << timestamp_str << " " << level_str << " " << message << std::endl;
}
