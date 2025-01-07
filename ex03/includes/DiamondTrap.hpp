/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:57:54 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 17:37:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

#include <iostream>

class DiamondTrap : public FragTrap, public ScavTrap
{
	private:
		std::string	name;

	public:
		DiamondTrap ();
		DiamondTrap (std::string name);

		DiamondTrap (const DiamondTrap &other);

		DiamondTrap& operator=(const DiamondTrap &other);

		~DiamondTrap();

		using ScavTrap::attack;

		void	whoAmI();
};

#endif
