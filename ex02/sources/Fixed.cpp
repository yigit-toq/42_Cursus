/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:17:08 by ytop              #+#    #+#             */
/*   Updated: 2025/01/02 17:56:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;

	this->value = 0;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;

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

Fixed::Fixed(const int value)
{
	std::cout << "Int constructor called" << std::endl;
	this->value = value << this->fracBits;
	std::cout << "Value of this Int externally is -> " << value << std::endl;
	std::cout << "Value of this Int internally is -> " << this->value << std::endl;
}

Fixed::Fixed(const float value)
{
	std::cout << "Float constructor called." << std::endl;
	this->value = roundf(value * (1 << this->fracBits));
	std::cout << "Value of this Float externally is -> " << value << std::endl;
	std::cout << "Value of this Float internally is -> " << this->value << std::endl;
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

Fixed	Fixed::operator+(const Fixed &other) const
{
	return (Fixed(this->toFloat() + other.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &other) const
{
	return (Fixed(this->toFloat() - other.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &other) const
{
	return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &other) const
{
	return (Fixed(this->toFloat() / other.toFloat()));
}

Fixed &Fixed::operator++()
{
	this->value++;
	return (*this);
}

Fixed &Fixed::operator--()
{
	this->value--;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed fixed;

	fixed = *this;
	this->value++;
	return (fixed);
}

Fixed Fixed::operator--(int)
{
	Fixed fixed;

	fixed = *this;
	this->value--;
	return (fixed);
}

bool	Fixed::operator>(const Fixed &other) const
{
	return (this->toFloat() > other.toFloat());
}

bool	Fixed::operator<(const Fixed &other) const
{
	return (this->toFloat() < other.toFloat());
}

bool	Fixed::operator>=(const Fixed &other) const
{
	return (this->toFloat() >= other.toFloat());
}

bool	Fixed::operator<=(const Fixed &other) const
{
	return (this->toFloat() <= other.toFloat());
}

bool	Fixed::operator==(const Fixed &other) const
{
	return (this->toFloat() == other.toFloat());
}

bool	Fixed::operator!=(const Fixed &other) const
{
	return (this->toFloat() != other.toFloat());
}

Fixed&	Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

Fixed&	Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

const Fixed&	Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b ? a : b);
}

const Fixed&	Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b ? a : b);
}
