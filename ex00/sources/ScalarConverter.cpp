/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:18:34 by ytop              #+#    #+#             */
/*   Updated: 2025/05/13 19:18:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

void	ScalarConverter::convert(const std::string &literal)
{
	std::cout << Y_CLR << "Literal: " << literal << RESET << std::endl;
}

#pragma region Utils

bool ScalarConverter::isInt(const std::string &literal)
{
	return (false);
}

bool ScalarConverter::isChar(const std::string &literal)
{
	return (false);
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	return (false);
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	return (false);
}

#pragma endregion

#pragma region Constructors

ScalarConverter::ScalarConverter()
{
	std::cout << R_CLR << "Constructor called" << RESET << std::endl;
}

ScalarConverter::~ScalarConverter()
{
	std::cout << R_CLR << "Destructor  called" << RESET << std::endl;
}

ScalarConverter:: ScalarConverter(const ScalarConverter &other)
{
	*this = other;

	std::cout << Y_CLR << "Copy const  called" << RESET << std::endl;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	if (this != &other)
	{
		*this = other;
	}

	std::cout << Y_CLR << "Copy assignment operator called" << RESET << std::endl;

	return (*this);
}

#pragma endregion
