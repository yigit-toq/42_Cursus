/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:11:05 by ytop              #+#    #+#             */
/*   Updated: 2025/01/03 15:57:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

Phonebook::Phonebook()
{
	this->index = 0;
	this->count = 0;
}

std::string const	Contact::fields_names[5] = 
{
	"First Name",
	"Last Name",
	"Nick Name",
	"Phone Number",
	"Darkest Secret"
};

std::string	Contact::GetNames(int index)
{
	return (this->fields_names[index]);
}

std::string	Contact::GetValue(int index)
{
	return (this->fields_value[index]);
}

void		Contact::SetValue(int index, std::string value)
{
	this->fields_value[index] = value;
}

int	ft_read_line(std::string &line)
{
	std::getline(std::cin, line);
	if (line.empty())
	{
		if (std::cin.eof())
		{
			std::cout << std::endl << "Goodbye :D" << std::endl;
			exit (0);
		}
		return (1);
	}
	return (0);
}
