/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:08:06 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 17:42:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

#include <iostream>

int	main()
{
	Data		d		= {42, "Yigit"};

	uintptr_t	r		= Serializer::  serialize	(&d);

	Data*		p		= Serializer::deserialize	( r);

	if (p == &d)
	{
		std::cout << G_CLR << "Successfully deserialized!\n" << RESET << std::endl;

		std::cout << "ID:	" << p->id		<< std::endl;
		std::cout << "Name:	" << p->name	<< std::endl;
	}
	else
	{
		std::cerr << "Error: Pointer is not match!\n";
	}
	return (0);
}
