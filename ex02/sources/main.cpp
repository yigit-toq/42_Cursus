/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:07:20 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:40:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main()
{
	std::string	string;
	std::string	*stringPTR;
	std::string	&stringREF = string;

	stringPTR = &string;

	string = "HI THIS IS BRAIN";

	std::cout << "Memory addres of string   : " << &string		<< std::endl;

	std::cout << "Memory addres of stringPTR: " << stringPTR	<< std::endl;
	std::cout << "Memory addres of stringREF: " << &stringREF	<< std::endl;

	std::cout << std::endl;

	std::cout << "Value of string   : " << 	string		<< std::endl;

	std::cout << "Value of stringPTR: " << *stringPTR	<< std::endl;
	std::cout << "Value of stringREF: " <<  stringREF	<< std::endl;
}
