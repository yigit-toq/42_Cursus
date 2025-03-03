/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:14 by ytop              #+#    #+#             */
/*   Updated: 2025/03/03 17:43:29 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

#include <sstream>

std::string itoa(int value)
{
	std::ostringstream	oss;

	oss << value;

	return (oss.str());
}

int main()
{
	{
		Animal*	dog = new Dog();
		std::cout << std::endl;
		Animal*	cat = new Cat();
		std::cout << std::endl;

		delete dog;
		std::cout << std::endl;
		delete cat;
	}

	{
		std::cout << "_________________________" << std::endl;

		int		size = 4;
		Animal*	animals[size];

		for (int i = 0; i < size; i++)
		{
			std::cout << std::endl;
			if (i % 2 == 0)
				animals[i] = new Dog();
			else
				animals[i] = new Cat();
		}
		for (int i = 0; i < size; i++)
		{
			std::cout << std::endl;
			delete animals[i];
		}	
	}

	std::cout << "_________________________\n" << std::endl;

	{
		std::cout << W_C << "Test with copy constructor" << E_C << std::endl;
		std::cout << std::endl;
		
		Cat	base_cat;

		std::cout << std::endl;
		std::cout << &base_cat << std::endl;
		std::cout << base_cat.getBrain() << std::endl;
		std::cout << std::endl;
		for (int i = 0; i < 10; i++)
		{
			base_cat.setIdea(i, "Idea " + itoa(i + 1));
		}

		Cat	copy_cat(base_cat);
		std::cout << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << W_C << copy_cat.getIdea(i) << E_C << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << &copy_cat << std::endl;
		std::cout << copy_cat.getBrain() << std::endl;
		std::cout << std::endl;

		std::cout << W_C << "Test with assignation operator" << E_C << std::endl;
		std::cout << std::endl;

		Dog	base_dog;

		std::cout << std::endl;
		std::cout << &base_dog << std::endl;
		std::cout << base_dog.getBrain() << std::endl;
		std::cout << std::endl;
		for (int i = 0; i < 10; i++)
		{
			base_dog.setIdea(i, "Idea " + itoa(i + 1));
		}

		Dog	copy_dog = base_dog;
		std::cout << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << W_C << copy_dog.getIdea(i) << E_C << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << &copy_dog << std::endl;
		std::cout << copy_dog.getBrain() << std::endl;
		std::cout << std::endl;
	}
	return (0);
}
