/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:16:52 by ytop              #+#    #+#             */
/*   Updated: 2025/07/27 17:41:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#pragma region Headers

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <cmath>

#pragma endregion

#define R_CLR "\033[1;31m"
#define G_CLR "\033[1;32m"
#define Y_CLR "\033[1;33m"
#define B_CLR "\033[1;34m"
#define W_CLR "\033[1;37m"
#define RESET "\033[0m"

enum e_type
{
	DOUBLE,
	FLOAT,
	CHAR,
	INT,
	UNDEF
};

class ScalarConverter
{
	private:
		 ScalarConverter			();
		 ScalarConverter			(const ScalarConverter	&other);

		~ScalarConverter			();

		 ScalarConverter &operator=	(const ScalarConverter	&other);

	public:
		static void	convert			(const std::string		&literal);

		class InvalidLiteralException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Invalid literal");
				}
		};
};

#endif
