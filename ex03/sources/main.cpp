/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:26:00 by ytop              #+#    #+#             */
/*   Updated: 2025/01/01 21:04:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int	main()
{
	Weapon club1 = Weapon("Lucille");
	HumanA bob("Bob", club1);
	bob.attack();
	club1.setType("some other type of club");
	bob.attack();

	Weapon club2 = Weapon("Arbalet");
	HumanB jim("Jim");

	jim.setWeapon(club2);

	jim.attack();
	club2.setType("some other type of club");
	jim.attack();
	return (0);
}
