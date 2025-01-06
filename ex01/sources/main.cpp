/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/06 14:28:58 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main()
{
	ScavTrap	Bob("Bob");
	ScavTrap	Jim("Jim");
	ScavTrap	Joe("Joe");

	Bob.attack("Jim");
	Jim.takeDamage(10);
	Jim.beRepaired(5);

	Joe.attack("Bob");
	Bob.takeDamage(10);
	Bob.beRepaired(5);

	return (0);
}
