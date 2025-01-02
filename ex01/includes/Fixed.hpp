/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:56 by ytop              #+#    #+#             */
/*   Updated: 2025/01/02 14:52:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		static const int	fracbits = 8;
		int					number;

	public:
		Fixed ();
		Fixed (const int value);

		Fixed (const Fixed& other);

		Fixed&	operator=(const Fixed& other);

		~Fixed();

		void	setRawBits( int const raw );
		int		getRawBits( void ) const;
};

#endif
