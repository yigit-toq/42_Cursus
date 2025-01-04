/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:47 by ytop              #+#    #+#             */
/*   Updated: 2025/01/02 14:49:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main()
{
	ClapTrap Bob("Bob");
	ClapTrap Jim("Jim");
	ClapTrap Joe("Joe");

	Bob.attack("Jim");
	Jim.takeDamage(10);
	Jim.beRepaired(5);

	Joe.attack("Bob");
	Bob.takeDamage(10);
	Bob.beRepaired(5);

	return (0);
}
