/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:56 by ytop              #+#    #+#             */
/*   Updated: 2025/02/27 16:26:35 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

#include <sstream>
#include <string>

#define C_Y	"\033[0;33m"
#define C_E "\033[0m"

class ClapTrap
{
	protected:
		std::string	name;
		int			hitPoints;
		int			energyPoints;
		int			attackDamage;

	public:
		ClapTrap ();
		ClapTrap (const std::string name);

		ClapTrap (const ClapTrap& other);

		ClapTrap& operator=(const ClapTrap& other);

		~ClapTrap();

		void	attack (const std::string& target);

		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		void	showStatus() const;

		std::string	getName() const;
};

std::string	itoa(int value);

#endif
