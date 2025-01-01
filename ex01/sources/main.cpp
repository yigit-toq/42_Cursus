/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:55:31 by ytop              #+#    #+#             */
/*   Updated: 2025/01/01 20:03:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

static std::string	getName();

int	main(int argc, char **argv)
{
	Zombie		*zombies;
	int			N;

	if (argc != 2)
		N = 10;
	else
		N = atoi(argv[1]);
	zombies = zombieHorde(N, getName());
	for (int i = 0; i < N; i++)
	{
		zombies[i].announce();
	}
	delete[] zombies;
	return (0);
}

static std::string	getName()
{
	std::string	name;

	while (TRUE)
	{
		std::cout << "Name the zombies: ";
		std::getline(std::cin, name);
		if (!name.empty())
			break ;
	}
	return (name);
}
