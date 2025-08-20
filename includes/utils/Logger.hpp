/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:31:16 by ytop              #+#    #+#             */
/*   Updated: 2025/08/07 00:41:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>

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
		 Logger			(const std::string& filename);
		~Logger			();

		static Logger*	_instance;
		std::ofstream	_file;

	public:
		static Logger& getInstance(const std::string& filename = "irc_server.log"); //

		static void destroyInstance(); //

		void	Log		(LogLevel level, const std::string& message); //
};

#endif
