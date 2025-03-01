/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:20:39 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 20:42:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

#define Y_C "\033[1;33m"
#define E_C "\033[0m"

class Brain
{
	private:
		std::string	ideas[100];

	public:
		Brain ();

		Brain(const Brain& other);

		Brain& operator=(const Brain& other);

		~Brain();

		void setIdea(int index, std::string idea);

		std::string getIdea(int index) const;
};

#endif
