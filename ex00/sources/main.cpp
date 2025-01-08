/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:14 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:06:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

#include "./wrong/WrongCat.hpp"

int main()
{
	const WrongAnimal*	wrong_cat;
	const Animal*		meta;
	const Animal*		cat;
	const Animal*		dog;	

	wrong_cat = new WrongCat();

	meta = new Animal();
	cat = new Cat();
	dog = new Dog();

	std::cout << wrong_cat->getType() << " " << std::endl;

	std::cout << dog->getType() << " " << std::endl;
	std::cout << cat->getType() << " " << std::endl;

	wrong_cat->makeSound();

	meta->makeSound();
	cat->makeSound();
	dog->makeSound();
	delete (wrong_cat);
	delete (meta);
	delete (cat);
	delete (dog);
	return (0);
}
