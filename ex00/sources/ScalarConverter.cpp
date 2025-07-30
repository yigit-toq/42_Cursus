/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:18:34 by ytop              #+#    #+#             */
/*   Updated: 2025/07/30 16:15:02 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#pragma region Constructors

ScalarConverter:: ScalarConverter	()
{
	std::cout << G_CLR << "Constructor called" << RESET << std::endl;
}

ScalarConverter::~ScalarConverter	()
{
	std::cout << R_CLR << "Destructor  called" << RESET << std::endl;
}

ScalarConverter:: ScalarConverter	(const ScalarConverter &other)
{
	*this = other;

	std::cout << Y_CLR << "Copy const  called" << RESET << std::endl;
}

ScalarConverter  &ScalarConverter::operator=(const ScalarConverter &other)
{
	if (this != &other)
	{
		*this = other;
	}

	std::cout << Y_CLR << "Copy assignment operator called" << RESET << std::endl;

	return (*this);
}

#pragma endregion

#pragma region Utils

static bool		isPseudoLiteral	(const std::string &literal)
{
	return (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "+inff" || literal == "-inff" || literal == "nanf");
}

static e_type	isType			(const std::string &literal)
{
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		return (CHAR);
	}

	if (isPseudoLiteral(literal))
	{
		return (literal[literal.length() - 1] == 'f' ? FLOAT : DOUBLE);
	}

	char* end = 0;

	long l = std::strtol(literal.c_str(), &end, 10);

	if (*end == 0 && l >= std::numeric_limits<int>::min() && l <= std::numeric_limits<int>::max())
	{
		return (INT);
	}

	end = 0;

	if (literal.find('.') != std::string::npos)
	{
		std::strtof(literal.c_str(), &end);

		if (*end == 'f' && *(end + 1) == 0)	return (FLOAT);
	}

	end = 0;

	std::strtod(literal.c_str(), &end);

	if (*end == 0)							return (DOUBLE);

	return (UNDEF);
}

static void	printInt	(double value)
{
	std::cout << "int:    ";

	if (std::isnan(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
	{
		std::cout << "impossible" << std::endl;
	}
	else
	{
		std::cout << static_cast<int>(value) << std::endl;
	}
}

static void	printChar	(double value)
{
	std::cout << "char:   ";

	if (std::isnan(value) || value < 0 || value > 127)
	{
		std::cout << "impossible"		<< std::endl;
	}
	else if (std::isprint(static_cast<char>(value)) == 0)
	{
		std::cout << "Non displayable"	<< std::endl;
	}
	else
	{
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
	}
}

static void	printFloat	(double value)
{
	std::cout << "float:  " << static_cast<float>(value) << "f" << std::endl;
}

static void	printDouble	(double value)
{
	std::cout << "double: " << value << std::endl;
}

static void	allPrinter	(double value)
{
	printChar	(value);

	printInt	(value);
	printFloat	(value);
	printDouble	(value);
}

static void	convertFromInt		(int	i)
{
	allPrinter(static_cast<double>(i));
}

static void	convertFromChar		(char	c)
{
	allPrinter(static_cast<double>(c));
}

static void	convertFromFloat	(float	f)
{
	allPrinter(static_cast<double>(f));
}

static void	convertFromDouble	(double	d)
{
	allPrinter(d);
}

static void convertFromPseudo	(std::string const& input)
{
	double d = (input[input.length() - 1] == 'f') ? std::strtof(input.c_str(), 0) : std::strtod(input.c_str(), 0);

	allPrinter(d);
}

#pragma endregion

void	ScalarConverter::convert(const std::string &literal)
{
	e_type type = isType(literal);

	switch (type)
	{
		case CHAR:
			convertFromChar(literal[1]);
			break;

		case INT:
			convertFromInt(std::atoi(literal.c_str()));
			break;

		case FLOAT:
			(isPseudoLiteral(literal)) ? convertFromPseudo(literal) : convertFromFloat	(std::strtof(literal.c_str(), 0));
			break;

		case DOUBLE:
			(isPseudoLiteral(literal)) ? convertFromPseudo(literal) : convertFromDouble	(std::strtod(literal.c_str(), 0));
			break;

		default:
			throw InvalidLiteralException();
	}
}
