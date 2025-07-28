/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:01:58 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 23:20:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int	main()
{
	try
	{
		Array<int> a; // Empty array

		std::cout << B_CLR << "Empty array size: " << a.size() << std::endl;

		std::cout << std::endl;

		Array<int> b(5);

		std::cout << B_CLR << "Array b: ";

		for (size_t i = 0; i < b.size(); ++i)
		{
			std::cout << b[i] << ' ';
		}

		std::cout << std::endl;

		for (size_t i = 0; i < b.size(); ++i)
		{
			b[i] = static_cast<int>(i) * 10;
		}

		std::cout << std::endl;
		Array<int> c = b;
		std::cout << std::endl;

		std::cout << Y_CLR << "Copied  array c from b  :	" << B_CLR;

		for (size_t i = 0; i < c.size(); ++i)
		{
			std::cout << c[i] << ' ';	
		}

		std::cout << std::endl;

		c[0] = 999; // Change c and verify b is unaffected

		std::cout << std::endl;
		std::cout << "Modified c[0] = 999" << std::endl;
		std::cout << std::endl;

		std::cout << Y_CLR << "Array b after c modified: 	" << B_CLR;

		for (size_t i = 0; i < b.size(); ++i)
		{
			std::cout << b[i] << ' ';
		}

		std::cout << std::endl;
		std::cout << std::endl;

		Array<std::string> words(2); // String array

		words[0] = "Hello";
		words[1] = "World";

		std::cout << Y_CLR << "String array: " << B_CLR;

		for (size_t i = 0; i < words.size(); ++i)
		{
			std::cout << words[i] << ' ';
		}

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << Y_CLR << "Trying to access out-of-bounds index..."	<< RESET << std::endl; // Out of bounds access

		std::cout << std::endl;

		std::cout << words[10];
	}
	catch (const std::exception& e)
	{
		std::cerr << B_CLR << "Exception caught: " << R_CLR << e.what()	<< RESET << std::endl;
	}
	return (0);
}
