/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 17:30:51 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int	main()
{
	DiamondTrap	Bob("Bob");
	DiamondTrap	Jim("Jim");
	DiamondTrap	Joe("Joe");

	Bob.attack("Jim");
	Jim.takeDamage(10);
	Jim.beRepaired(5);

	Joe.attack("Bob");
	Bob.takeDamage(10);
	Bob.beRepaired(5);

	Joe.whoAmI();

	return (0);
}
