#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#include <fstream>

#include <string>

enum LogLevel
{
	INFO,
	DEBUG,
	ERROR,
	WARNING,
};

class Logger
{
	private:
		static Logger*	_instance;

		std::ofstream	_file;

	private:
		 Logger			(const std::string& filename);
		~Logger			();

	public:
		static	Logger&	GetInstance	(const std::string& filename = "irc_server.log");

		static	void	RmvInstance	();

	public:
				void	Log			(LogLevel level, const std::string& message);
};

#endif
