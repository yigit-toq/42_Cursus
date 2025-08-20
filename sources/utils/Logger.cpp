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

typedef struct tm tm;

Logger* Logger::_instance = NULL;

Logger& Logger::getInstance(const std::string& filename)
{
	if (_instance == NULL)
	{
		_instance = new Logger(filename);
	}
	return (*_instance);
}

void Logger::destroyInstance()
{
	if (_instance != NULL)
	{
		delete _instance;
		_instance = NULL;
	}
}

Logger::Logger(const std::string& filename)
{
	_file.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);

	if (!_file.is_open())
	{
		std::cerr << "Log file could not be opened: " << filename << std::endl;
	}
}

Logger::~Logger()
{
	if (_file.is_open())
	{
		_file.close();
	}
}

void	Logger::Log(LogLevel level, const std::string& message)
{
	if (!_file.is_open())
	{
		std::cerr << "The log file is not open. The message is being written to the console." << std::endl;
		std::cerr << "[ERROR] " << message << std::endl;
		return ;
	}

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

	time_t	now = time(0);
	tm* 	ltm = localtime(&now);

	strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", ltm);

	_file << timestamp_str << " " << level_str << " " << message << std::endl;

	if (level == ERROR)
	{
		std::cerr << timestamp_str << " " << level_str << " " << message << std::endl;
	}
}
