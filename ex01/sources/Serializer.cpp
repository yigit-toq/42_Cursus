/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:06:45 by ytop              #+#    #+#             */
/*   Updated: 2025/07/28 13:12:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

uintptr_t	Serializer::serialize	(Data* ptr)
{
	return reinterpret_cast<uintptr_t>	(ptr);
}

Data*		Serializer::deserialize	(uintptr_t raw)
{
	return reinterpret_cast<Data*>		(raw);
}
