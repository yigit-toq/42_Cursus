/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:01:58 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 23:25:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int	main()
{
	int a = 2;
	int b = 3;

	::swap( a, b );

	std::cout << B_CLR << "a = " << Y_CLR << a << std::endl;
	std::cout << B_CLR << "b = " << Y_CLR << b << std::endl;
	std::cout << RESET << std::endl;

	std::cout << B_CLR << "min( a, b ) = " << Y_CLR << ::min( a, b ) << RESET << std::endl;
	std::cout << B_CLR << "max( a, b ) = " << Y_CLR << ::max( a, b ) << RESET << std::endl;

	std::cout << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);

	std::cout << B_CLR << "c = " << Y_CLR << c << std::endl;
	std::cout << B_CLR << "d = " << Y_CLR << d << std::endl;
	std::cout << RESET << std::endl;

	std::cout << B_CLR << "min( c, d ) = " << Y_CLR << ::min( c, d ) << RESET << std::endl;
	std::cout << B_CLR << "max( c, d ) = " << Y_CLR << ::max( c, d ) << RESET << std::endl;

	return (0);
}
