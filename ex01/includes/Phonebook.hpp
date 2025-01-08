/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:19:13 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 18:18:06 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include <sstream>

#include <stdlib.h>
#include <string>

# define FIELD_WIDTH	10

class Contact
{
	private:
		static const std::string	fields_names[5];

		std::string					fields_value[5];

	public:
		std::string	GetNames(int index);
		std::string	GetValue(int index);

		void		SetValue(int index, std::string value);
};

class Phonebook
{
	private:
		Contact		contact[8];
		int			index;
		int			count;
	public:
		Phonebook();
		void	Add();
		void	Search();
};

bool	ft_read_line(std::string &line);

#endif
