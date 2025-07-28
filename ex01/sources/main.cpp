/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:08:06 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 13:27:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int	main()
{
	Data		data	= {42, "Yigit"};

	uintptr_t	raw		= Serializer::serialize		(&data);

	Data*		ptr		= Serializer::deserialize	(raw);

	if (ptr == &data)
	{
		std::cout << G_CLR << "Successfully deserialized!\n" << RESET << std::endl;

		std::cout << "ID:	" << ptr->id	<< std::endl;
		std::cout << "Name:	" << ptr->name	<< std::endl;
	}
	else
	{
		std::cerr << "Error: Pointer is not match!\n";
	}
	return (0);
}
