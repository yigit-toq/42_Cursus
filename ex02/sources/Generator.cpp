/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:28:42 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 14:40:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Generator.hpp"
#include "Derived.hpp"

Base* generate()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	int random = std::rand() % 3;

	switch (random)
	{
		case 0:
			return new A();
		case 1:
			return new B();
		case 2:
			return new C();
		default:
			return (0);
	}
}

void	identify(Base* p)
{
		 if (dynamic_cast<A*>(p))
	{
		std::cout << "A" << std::endl;	
	}
	else if (dynamic_cast<B*>(p))
	{
		std::cout << "B" << std::endl;	
	}
	else if (dynamic_cast<C*>(p))
	{
		std::cout << "C" << std::endl;
	}
	else
	{
		std::cout << "Unknown type" << std::endl;
	}
}

void	identify(Base& p)
{
	try
	{
				(void)dynamic_cast<A&>(p);

				std::cout << "A" << std::endl;
	}
	catch(...)
	{
		try
		{
				(void)dynamic_cast<B&>(p);

				std::cout << "B" << std::endl;
		}
		catch(...)
		{
			try
			{
				(void)dynamic_cast<C&>(p);

				std::cout << "C" << std::endl;
			}
			catch(...)
			{
				std::cout << "Unknown type" << std::endl;
			}
		}
		
	}
	
}
