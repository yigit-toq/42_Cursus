/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:05:49 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 17:49:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>

#include "Data.hpp"

#define R_CLR "\033[1;31m"
#define G_CLR "\033[1;32m"
#define Y_CLR "\033[1;33m"
#define B_CLR "\033[1;34m"
#define W_CLR "\033[1;37m"
#define RESET "\033[0m"

class Serializer
{
	private:
		 Serializer						();
		 Serializer						(const Serializer	&other);

		~Serializer						();

		 Serializer &operator=			(const Serializer	&other);

	public:
		static uintptr_t	serialize	(Data* ptr);

		static Data*		deserialize	(uintptr_t raw);
};

#endif
