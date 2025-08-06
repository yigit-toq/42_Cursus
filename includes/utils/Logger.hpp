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
#include <iostream>

class Logger
{
	private:
		 Logger 		();
		~Logger			();

	public:
		enum LogLevel
		{
			INFO,
			DEBUG,
			ERROR,
			WARNING,
		};

		static void	Log	(LogLevel level, const std::string& message);
};

#endif
