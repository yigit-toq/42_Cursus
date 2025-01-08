/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:01:44 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 18:06:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		while (argv[++i])
		{
			j = 0;
			while (argv[i][j])
			{
				argv[i][j] = toupper(argv[i][j]);
				j++;
			}
			std::cout << argv[i] << std::endl;
		}
	}
}
