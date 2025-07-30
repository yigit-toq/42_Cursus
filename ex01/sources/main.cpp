/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:01:58 by ytop              #+#    #+#             */
/*   Updated: 2025/07/30 21:22:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "iter.hpp"

int	main()
{
	{
				int arr		[] = {1, 2, 3, 4, 5};

		const	int constArr[] = {10, 20, 30};

		std::cout << Y_CLR << "Org	int array: " << RESET;

		iter(arr, 5, print<int>);

		std::cout << std::endl;

		std::cout << Y_CLR << "Inc	int array: " << RESET;

		iter(arr, 5, increment	<int>);
		iter(arr, 5, print		<int>);

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << Y_CLR << "Const	int array: " << RESET;

		iter(constArr, 3, print<int>);

		std::cout << std::endl;
		std::cout << std::endl;
	}

	{
				std::string arr			[]	= {"Hello", "World", "42"};

		const	std::string constArr	[]	= {"C++", "is", "fun"};

		std::cout << Y_CLR << "Org	string array: " << RESET;

		iter(arr, 3, print<std::string>);

		std::cout << std::endl;

		std::cout << Y_CLR << "Upr	string array: " << RESET;

		iter(arr, 3, upperCase<std::string>);
		iter(arr, 3, print<std::string>);

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << Y_CLR << "Const	string array: " << RESET;

		iter(constArr, 3, print<std::string>);

		std::cout << std::endl;
	}

	return (0);
}
