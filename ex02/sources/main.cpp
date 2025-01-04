/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/02 17:56:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main( void )
{
	Fixed		a;
	Fixed const	b(Fixed( 5.05f ) * Fixed( 2 ));

	std::cout << a << std::endl;

	std::cout << ++a << std::endl;

	std::cout << a++ << std::endl;

	std::cout << a << std::endl;
	std::cout << b << std::endl;

	std::cout << "max: " << Fixed::max( a, b ) << std::endl;
	return (0);
}
