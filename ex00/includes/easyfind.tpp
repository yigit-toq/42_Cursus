/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:13:27 by ytop              #+#    #+#             */
/*   Updated: 2025/07/29 22:17:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_TPP
#define EASYFIND_TPP

#include "easyfind.hpp"

template <typename T>
typename T::const_iterator	easyfind(const T& container, int value)
{
	typename T::const_iterator it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
		throw NotFoundException();

	return (it);
}

#endif
