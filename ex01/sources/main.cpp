/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:53:01 by ytop              #+#    #+#             */
/*   Updated: 2025/01/09 00:53:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

static void	header(void)
{
	std::cout << C_Y;
	std::cout << ".--. .   . .--. .   ..---. .--.  .--.  .--. .   .  " << std::endl;
	std::cout << "|   )|   |:    :|\\  ||     |   ):    ::    :|  /  " << std::endl;
	std::cout << "|--' |---||    || \\ ||---  |--: |    ||    ||-'   " << std::endl;
	std::cout << "|    |   |:    ;|  \\||     |   ):    ;:    ;|  \\ " << std::endl;
	std::cout << "'    '   ' `--' '   ''---' '--'  `--'  `--' '   `  " << std::endl << std::endl;
	std::cout << END;
}

int	main(void)
{
	Phonebook	pbook;
	std::string	input;

	header();
	std::cout << C_B;
	std::cout << "1) Add a new contact     -> [ADD]"	<< std::endl;
	std::cout << "2) Exit the phonebook    -> [EXIT]"	<< std::endl;
	std::cout << "3) Search for a contact  -> [SEARCH]"	<< std::endl << std::endl;
	std::cout << END;

	while (true)
	{
		std::cout << C_Y << "Enter your choice: " << END;
		if (!ft_read_line(input))
		{
			continue ;
		}
		if (input == "ADD")
		{
			pbook.Add();
		}
		else if (input == "EXIT")
		{
			break ;
		}
		else if (input == "SEARCH")
		{
			pbook.Search();
		}
		else
		{
			std::cout << C_R << "Invalid Input" << END << std::endl;
		}
	}
	return (0);
}
