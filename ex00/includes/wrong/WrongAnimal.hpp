/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:20:12 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:52:58 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

#define B_C "\033[1;34m"
#define Y_C "\033[1;33m"
#define G_C "\033[1;32m"
#define R_C "\033[1;31m"
#define E_C "\033[0m"

class WrongAnimal
{
	protected:
		std::string type;

	public:
		WrongAnimal ();

		WrongAnimal (const WrongAnimal& other);

		WrongAnimal& operator=(const WrongAnimal& other);

		~WrongAnimal();

		void makeSound() const;

		std::string getType() const;
};

#endif
