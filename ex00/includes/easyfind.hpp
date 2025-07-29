/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:05:37 by ytop              #+#    #+#             */
/*   Updated: 2025/07/29 22:22:28 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>
#include <algorithm>
#include <iterator>

class NotFoundException : public std::exception
{
	public:
		const char* what() const throw()
		{
			return ("Value not found in the container.");
		}
};

template <typename T>
typename T::const_iterator	easyfind(const T& container, int value);

#include "easyfind.tpp"

#endif
