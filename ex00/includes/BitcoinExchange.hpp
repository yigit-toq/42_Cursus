/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:52:04 by ytop              #+#    #+#             */
/*   Updated: 2025/12/04 15:42:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_database;

		bool	isValidDates	(const  std::string& date) const;
		bool	isValidValue	(double value) const;

		bool	isLeapYear		(int year) const;

		void	trimString		(std::string& str) const;

		double	findRate		(const std::string& date) const;

		bool	parseDate		(const std::string& date, int& year, int& month, int& day) const;

	public :
		 BitcoinExchange			();
		 BitcoinExchange			(const BitcoinExchange& other);
		 BitcoinExchange& operator=	(const BitcoinExchange& other);
		~BitcoinExchange			();

		void	LoadDatabase		(const std::string& filename);
		void	ProcessInput		(const std::string& filename);
};

#endif
