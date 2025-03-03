/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:14 by ytop              #+#    #+#             */
/*   Updated: 2025/03/03 17:35:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	// Animal	animal;

	Animal* dog = new Dog();
	std::cout << std::endl;
	Animal* cat = new Cat();
	std::cout << std::endl;
	std::cout << dog->getType() << " " << std::endl;
	std::cout << cat->getType() << " " << std::endl;
	std::cout << std::endl;
	cat->makeSound();
	dog->makeSound();
	std::cout << std::endl;
	delete dog;
	delete cat;
	return (0);
}
