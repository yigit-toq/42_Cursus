/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:20:12 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:11:27 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

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
