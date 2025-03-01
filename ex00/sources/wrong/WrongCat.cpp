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
	this->type = "WrongCat";

	std::cout << R_C;
	std::cout << "WrongCat constructor called" << std::endl;
	std::cout << E_C;
}

// WrongCat::WrongCat(const WrongCat& other)
// {
// 	std::cout << R_C << "WrongCat copy constructor called" << E_C << std::endl;
//
// 	*this = other;
// }

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << R_C << "WrongCat assignation operator called" << E_C << std::endl;

	if (this != &other)
		this->type = other.type;

	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << R_C << "WrongCat destructor called" << E_C << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << R_C << "WrongCat sound" << E_C << std::endl;
}
