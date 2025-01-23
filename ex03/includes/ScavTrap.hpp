/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:18:30 by ytop              #+#    #+#             */
/*   Updated: 2025/01/23 18:55:30 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>

class ScavTrap : public virtual ClapTrap
{
	private:

	public:
		ScavTrap ();
		ScavTrap (std::string name);

		ScavTrap (const ScavTrap &other);

		ScavTrap &operator=(const ScavTrap &other);

		~ScavTrap();

		void	attack (const std::string& target);

		void	guardGate();

		int		getEnergyPoints() const;
};

#endif
