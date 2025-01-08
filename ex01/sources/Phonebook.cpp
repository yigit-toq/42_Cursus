/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:18:45 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 18:20:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

Phonebook::Phonebook()
{
	this->index = 0;
	this->count = 0;
}

void	Phonebook::Add()
{
	std::string	input;
	int			i;

	i = 0;
	while (i < 5)
	{
		std::cout << C_G << "Enter " << this->contact[this->index].GetNames(i) << ":	" << END;
		if (!ft_read_line(input) || input[0] == ' ' || input.find('\t', 0) != std::string::npos)
			continue ;
		this->contact[this->index].SetValue(i, input);
		i++;
	}
	count = (count < 8) ? count + 1 : 8;
	index = (index < 7) ? index + 1 : 0;
}

void	Phonebook::Search()
{
	std::string	input;
	std::string	value;
	int			index;

	if (!this->count)
	{
		std::cout << C_R << "No contacts available" << END << std::endl;
		return ;
	}
	std::cout << std::setw(FIELD_WIDTH) << "Index";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "|" << std::setw(FIELD_WIDTH) << this->contact[0].GetNames(i);
	}
	std::cout << "|" << std::endl;
	for (int i = 0; i < count; i++)
	{
		std::cout << std::setw(FIELD_WIDTH) << i + 1 << "|";

		for (int j = 0; j < 3; j++)
		{
			value = this->contact[i].GetValue(j);

			if (value.length() > FIELD_WIDTH)
				value = value.substr(0, FIELD_WIDTH - 1) +  ".";

			std::cout << std::setw(FIELD_WIDTH) << value << "|";
		}
		std::cout << std::endl;
	}

	std::cout << C_Y << "Enter index: " << END;
	if (!ft_read_line(input))
	{
		return ;
	}
	std::istringstream(input) >> index;
	if (index > 0 && index <= this->count)
	{
		std::cout << C_B;
		for (int i = 0; i < 5; i++)
		{
			std::cout << this->contact[index - 1].GetNames(i) << ":	" << this->contact[index - 1].GetValue(i) << std::endl;
		}
		std::cout << END;
	}
	else
	{
		std::cout << C_R << "Invalid index" << END << std::endl;
	}
}
