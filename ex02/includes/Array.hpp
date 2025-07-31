/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:34:16 by ytop              #+#    #+#             */
/*   Updated: 2025/07/31 15:40:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

#define R_CLR "\033[1;31m"
#define G_CLR "\033[1;32m"
#define Y_CLR "\033[1;33m"
#define B_CLR "\033[1;34m"
#define W_CLR "\033[1;37m"
#define RESET "\033[0m"

template <typename T>
class Array
{
	private:
		T				*data;
		unsigned int	_size;

	public:
		 Array				(unsigned int n);
		 Array				();
		~Array				();

		Array				(const Array &other);

		Array	&operator=	(const Array &other);

		T		&operator[]	(unsigned int index);
		const T &operator[]	(unsigned int index) const;

		unsigned int size	() const;
};

template <typename T>
Array<T>:: Array(unsigned int n) : _size(n)
{
	data = new T[n];

	std::cout << G_CLR << "Array of size " << n << " created."	<< RESET << std::endl;
}

template <typename T>
Array<T>:: Array() : data(0), _size(0)
{
	std::cout << G_CLR << "Default Array created."				<< RESET << std::endl;
}

template <typename T>
Array<T>::~Array()
{
	delete[] (data);

	std::cout << R_CLR << "Array des."							<< RESET << std::endl;
}

template <typename T>
Array<T>:: Array(const Array &other) : _size(other._size)
{
	data = new T[_size];

	for (unsigned int i = 0; i < _size; ++i)
	{
		data[i] = other.data[i];
	}

	std::cout << Y_CLR << "Array cpy."							<< RESET << std::endl;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
	if (this != &other)
	{
		delete[] (data);

		this->_size = other._size;

		data = new T[_size];

		for (unsigned int i = 0; i < _size; ++i)
		{
			data[i] = other.data[i];
		}
	}
	return (*this);

	std::cout << Y_CLR << "Array ass."							<< RESET << std::endl;
}

template <typename T>
T		&Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
	{
		throw std::out_of_range("Index is out of bounds");
	}
	return (data[index]);
}

template <typename T>
const T	&Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
	{
		throw std::out_of_range("Index is out of bounds");
	}
	return (data[index]);
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (_size);
}

#endif
