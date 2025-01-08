/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:24:26 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 19:56:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wrong/WrongCat.hpp"

WrongCat::WrongCat()
{
	type = "WrongCat";

	std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other)
{
	*this = other;

	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	type = other.type;
	std::cout << "WrongCat assignation operator called" << std::endl;

	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << "WrongMeow WrongMeow" << std::endl;
}
