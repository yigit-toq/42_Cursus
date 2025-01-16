/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:17:08 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 13:30:58 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Constructor called" << std::endl;

	this->value = 0;
}

Fixed::Fixed(const int value)
{
	std::cout << "Int	constructor called" << std::endl;
	this->value = value << this->fracBits;
}

Fixed::Fixed(const float value)
{
	std::cout << "Float	constructor called" << std::endl;
	this->value = roundf(value * (1 << this->fracBits));
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy	constructor called" << std::endl;

	this->value = other.getRawBits();
}

Fixed	&Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;

	this->value = other.getRawBits();

	return (*this);
}

int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;

	return (this->value);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;

	this->value = raw;	
}

Fixed::~Fixed()
{
	std::cout << "Destructor  called" << std::endl;
}

int		Fixed::toInt	(void) const
{
	return (roundf(this->value / (1 << this->fracBits)));
}

float	Fixed::toFloat	(void) const
{
	return (float(this->value / (float)(1 << this->fracBits)));
}

std::ostream	&operator<<(std::ostream &string, const Fixed &other)
{
	string << other.toFloat();
	return (string);
}
