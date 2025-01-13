/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:55:31 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:37:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main()
{
	Zombie	*zombie;

	zombie = newZombie("Heap");
	zombie->announce();

	delete(zombie);

	std::cout << std::endl;

	randomChup("Stack");

	return (0);
}
