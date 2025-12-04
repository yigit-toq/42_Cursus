/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:05:46 by ytop              #+#    #+#             */
/*   Updated: 2025/12/04 15:47:31 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

#include <sstream>
#include <cstdlib>

#include <iostream>

class RPN
{
	private:
		std::stack<int>	_stack;
		
		bool	isOperator		(const std::string& token) const;
		bool	isValidNumber	(const std::string& token) const;

		int		performOperation(int a, int b, char op) const;

	public :
		 RPN			();
		 RPN			(const RPN& other);
		 RPN& operator=	(const RPN& other);
		~RPN			();

		int	Calculate	(const std::string& expression);
};

#endif
