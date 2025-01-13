/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:00:38 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:37:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

#include <stdlib.h>

class Zombie
{
	private:
		std::string name;

	public:
		Zombie ();
		Zombie (std::string name);

		~Zombie();

		void	announce();
		void	add_name(std::string name);
};

Zombie	*zombieHorde(int N, std::string name);

#endif
