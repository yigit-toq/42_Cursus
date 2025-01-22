/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/22 16:26:27 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main()
{
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;

	std::cout << ++a << std::endl;

	std::cout << a << std::endl;

	std::cout << a++ << std::endl;

	std::cout << a << std::endl;
	std::cout << b << std::endl;

	std::cout << Fixed::max( a, b ) << std::endl;

	Fixed	n1(45.10f);
	Fixed	n2(42);

	std::cout << "n1 = " << n1 << std::endl;
	std::cout << "n2 = " << n2 << std::endl;

	std::cout << "n1 + n2 = " << n1 + n2 << std::endl;
	std::cout << "n1 - n2 = " << n1 - n2 << std::endl;
	std::cout << "n1 * n2 = " << n1 * n2 << std::endl;
	std::cout << "n1 / n2 = " << n1 / n2 << std::endl;

	return (0);
}
