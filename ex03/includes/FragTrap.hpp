/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:13:32 by ytop              #+#    #+#             */
/*   Updated: 2025/01/07 17:12:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

#include <iostream>

class FragTrap : public virtual ClapTrap
{
	private:

	public:
		FragTrap ();
		FragTrap (std::string name);

		FragTrap (const FragTrap &other);

		FragTrap &operator=(const FragTrap &other);

		~FragTrap();

		void	attack (const std::string& target);

		void	highFivesGuys();
};

#endif
