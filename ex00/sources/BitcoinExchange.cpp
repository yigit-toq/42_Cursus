/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:52:07 by ytop              #+#    #+#             */
/*   Updated: 2025/12/01 23:52:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange:: BitcoinExchange() {}

BitcoinExchange:: BitcoinExchange(const BitcoinExchange& other) { *this = other; }

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_database = other._database;
	}

	return (*this);
}

void	BitcoinExchange::trimString(std::string& str) const
{
	size_t	start	= str.find_first_not_of(" \t\n\r");
	size_t	end		= str.find_last_not_of (" \t\n\r");

	if (start == std::string::npos)
	{
		str = "";
		return	;
	}

	str = str.substr(start, end - start + 1);
}

bool	BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool	BitcoinExchange::parseDate(const std::string& date, int& year, int& month, int& day) const
{
	if (date.length() != 10)
	{
		return (false);
	}

	if (date[4] != '-' || date[7] != '-')
	{
		return (false);
	}

	std::string	yStr = date.substr(0, 4);
	std::string	mStr = date.substr(5, 2);
	std::string	dStr = date.substr(8, 2);

	for (size_t i = 0; i < yStr.length(); i++)
		if (!isdigit(yStr[i])) return (false);
	for (size_t i = 0; i < mStr.length(); i++)
		if (!isdigit(mStr[i])) return (false);
	for (size_t i = 0; i < dStr.length(); i++)
		if (!isdigit(dStr[i])) return (false);

	day		= atoi(dStr.c_str());
	year	= atoi(yStr.c_str());
	month	= atoi(mStr.c_str());

	return (true);
}

bool	BitcoinExchange::isValidDate(const std::string& date) const
{
	int	year, month, day;

	if (!parseDate(date, year, month, day))
	{
		return (false);
	}

	if (year  < 1000 || year  > 9999)
		return (false);

	if (month < 1    || month > 12  )
		return (false);

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (isLeapYear(year))
	{
		daysInMonth[1] = 29;
	}

	if (day < 1 || day > daysInMonth[month - 1])
	{
		return (false);
	}

	return (true);
}

bool	BitcoinExchange::isValidValue(double value) const
{
	return (value >= 0 && value <= 1000);
}

double	BitcoinExchange::findClosestRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _database.find(date);

	if (it != _database.end())
	{
		return (it->second);
	}

	it = _database.lower_bound(date);

	if (it == _database.begin())
	{
		return (it->second);
	}

	--it;

	return (it->second);
}

// ========== Ana Fonksiyonlar ==========

void	BitcoinExchange::LoadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
	{
		throw std::runtime_error("Error: could not open database file.");
	}

	std::string	line;

	std::getline(file, line);

	while (std::getline(file, line))
	{
		size_t pos = line.find(',');

		if (pos == std::string::npos)
			continue ;
		
		std::string	datStr = line.substr(0, pos);
		std::string	valStr = line.substr(pos + 1);
		
		trimString(datStr);
		trimString(valStr);
		
		double	value = atof(valStr.c_str());

		_database[datStr] = value;
	}

	file.close();
	
	if (_database.empty())
	{
		throw std::runtime_error("Error: database is empty.");
	}
}

void	BitcoinExchange::ProcessInput(const std::string& filename)
{
	std::ifstream	file(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	std::string	line;

	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue ;

		size_t pos = line.find('|');

		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		std::string datStr = line.substr(0, pos);
		std::string valStr = line.substr(pos + 1);

		trimString(datStr);
		trimString(valStr);

		if (!isValidDate(datStr))
		{
			std::cerr << "Error: bad input => " << datStr << std::endl;
			continue ;
		}

		char*	endptr;

		double	value = strtod(valStr.c_str(), &endptr);

		if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
		{
			std::cerr << "Error: bad input => " << valStr << std::endl;
			continue ;
		}

		if (value > 1000)
		{
			std::cerr << "Error: too large a number."		<< std::endl;
			continue ;
		}

		if (value < 0	)
		{
			std::cerr << "Error: not a positive number."	<< std::endl;
			continue ;
		}

		try
		{
			double	rate	= findClosestRate(datStr);
			double	result	= value * rate;

			std::cout << datStr << " => " << value << " = " << result << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	file.close();
}
