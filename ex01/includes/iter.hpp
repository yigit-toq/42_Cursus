/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:09:26 by ytop              #+#    #+#             */
/*   Updated: 2025/07/30 21:17:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#define R_CLR "\033[1;31m"
#define G_CLR "\033[1;32m"
#define Y_CLR "\033[1;33m"
#define B_CLR "\033[1;34m"
#define W_CLR "\033[1;37m"
#define RESET "\033[0m"

#include <cstddef>

template <typename T, typename Func>
void	iter		(T* array, size_t length, Func func)
{
	for (size_t i = 0; i < length; ++i)
	{
		func(array[i]);	
	}
}

template <typename T>
void	print		(const T &value)
{
	std::cout << B_CLR << value << " " << RESET;
}

template <typename T>
void	increment	(T &value)
{
	++value;
}

template <typename T>
void	decrement	(T &value)
{
	--value;
}

template <typename T>
void	upperCase	(T &value)
{
	for (size_t i = 0; i < value.length(); ++i)
	{
		if (value[i] >= 'a' && value[i] <= 'z')
		{
			value[i] -= ('a' - 'A');
		}
	}
}

#endif
