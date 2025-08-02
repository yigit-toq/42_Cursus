/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:06:06 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 12:05:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

#include <iostream>

#include <vector>
#include <deque>
#include <list>

void testFind(const std::string& name, const int value)
{
	try
	{
		if (name == "list")
		{
			std::list	<int>	l;
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);
			l.push_back(4);
			l.push_back(5);

			std::cout << "Found in list  : " << *easyfind(l, value) << std::endl;
		}
		else if (name == "deque" )
		{
			std::deque	<int>	d;
			d.push_back(1);
			d.push_back(2);
			d.push_back(3);
			d.push_back(4);
			d.push_back(5);

			std::cout << "Found in deque : " << *easyfind(d, value) << std::endl;
		}
		else if (name == "vector")
		{
			std::vector	<int>	v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
			v.push_back(5);

			std::cout << "Found in vector: " << *easyfind(v, value) << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error (" << name << "): " << e.what() << std::endl;
	}
}

int	main()
{
	testFind("vector"	, 0);
	testFind("deque"	, 1);
	testFind("list"		, 2);

	return (0);
}
