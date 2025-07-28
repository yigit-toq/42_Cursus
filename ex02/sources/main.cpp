/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:08:06 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 17:39:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Generator.hpp"

int	main()
{
	Base* obj = generate();

	std::cout << "identify(Base*): ";
	identify( obj);

	std::cout << "identify(Base&): ";
	identify(*obj);

	delete	( obj);

	return	(0);
}
