/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:56 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 13:29:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		static const int	fracBits = 8;
		int					value;

	public:
		Fixed ();
		Fixed (const int value);
		Fixed (const float value);

		Fixed (const Fixed& other);

		Fixed&	operator=(const Fixed& other);

		~Fixed();

		void	setRawBits( int const raw );
		int		getRawBits( void ) const;

		int		toInt	(void) const;
		float	toFloat	(void) const;
};

std::ostream&	operator<<(std::ostream &, const Fixed &);

#endif
