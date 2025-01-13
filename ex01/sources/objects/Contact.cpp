/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:11:05 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 12:08:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

std::string const Contact::fields_names[5] = 
{
	"First Name",
	"Last Name",
	"Nick Name",
	"Phone Number",
	"Darkest Secret"
};

std::string Contact::GetNames(int index)
{
	return (fields_names[index]);
}

std::string	Contact::GetValue(int index)
{
	return (this->fields_value[index]);
}

void Contact::SetValue(int index, std::string value)
{
	this->fields_value[index] = value;
}
