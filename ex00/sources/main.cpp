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
	const WrongAnimal*	wrong;
	const Animal*		base;
	const Animal*		cat;
	const Animal*		dog;

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "WrongAnimal() = new WrongCat()" << std::endl;
	std::cout << std::endl;
	wrong = new WrongCat();
	std::cout << std::endl;
	std::cout << "type: " << wrong->getType() << std::endl;
	std::cout << std::endl;
	wrong->makeSound();
	std::cout << std::endl;
	delete (wrong);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Animal() = new Animal()" << std::endl;
	std::cout << std::endl;
	base = new Animal();
	std::cout << std::endl;
	std::cout << "type: " << base->getType() << std::endl;
	std::cout << std::endl;
	base->makeSound();
	std::cout << std::endl;
	delete (base);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Animal() = new Cat()" << std::endl;
	std::cout << std::endl;
	base = new Cat();
	std::cout << std::endl;
	std::cout << "type: " << base->getType() << std::endl;
	std::cout << std::endl;
	base->makeSound();
	std::cout << std::endl;
	delete (base);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Animal() = new Dog()" << std::endl;
	std::cout << std::endl;
	base = new Dog();
	std::cout << std::endl;
	std::cout << "type: " << base->getType() << std::endl;
	std::cout << std::endl;
	base->makeSound();
	std::cout << std::endl;
	delete (base);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Cat() = new Cat()" << std::endl;
	std::cout << std::endl;
	cat = new Cat();
	std::cout << std::endl;
	std::cout << "type: " << cat->getType() << std::endl;
	std::cout << std::endl;
	cat->makeSound();
	std::cout << std::endl;
	delete (cat);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Cat() = new Dog()" << std::endl;
	std::cout << std::endl;
	cat = new Dog();
	std::cout << std::endl;
	std::cout << "type: " << cat->getType() << std::endl;
	std::cout << std::endl;
	cat->makeSound();
	std::cout << std::endl;
	delete (cat);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Dog() = new Dog()" << std::endl;
	std::cout << std::endl;
	dog = new Dog();
	std::cout << std::endl;
	std::cout << "type: " << dog->getType() << std::endl;
	std::cout << std::endl;
	dog->makeSound();
	std::cout << std::endl;
	delete (dog);

	std::cout << "______________________________" << std::endl;

	std::cout << std::endl;
	std::cout << "Dog() = new Cat()" << std::endl;
	std::cout << std::endl;
	dog = new Cat();
	std::cout << std::endl;
	std::cout << "type: " << dog->getType() << std::endl;
	std::cout << std::endl;
	dog->makeSound();
	std::cout << std::endl;
	delete (dog);

	std::cout << "______________________________" << std::endl;
	return (0);
}
