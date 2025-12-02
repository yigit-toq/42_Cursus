/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:59:39 by ytop              #+#    #+#             */
/*   Updated: 2025/12/02 17:59:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	try
	{
		PmergeMe	sorter;

		sorter.ParseInput	(argc, argv);
		sorter.Sort			();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
