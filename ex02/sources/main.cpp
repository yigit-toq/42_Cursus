/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:06:06 by ytop              #+#    #+#             */
/*   Updated: 2025/08/02 15:29:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

#include <iostream>
#include <list>

int main()
{
	std::cout << "--- MutantStack ---" << std::endl;

	std::cout << std::endl;

	MutantStack<int>	stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);

	std::cout << "Top element   : " << stack.top	() << std::endl;

	std::cout << std::endl;
	stack.pop();

	std::cout << "Stack contents: ";

	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "---  std::list  ---" << std::endl;

	std::cout << std::endl;

	std::list<int>		mlist;

	mlist.push_back(1);
	mlist.push_back(2);
	mlist.push_back(3);
	mlist.push_back(4);
	mlist.push_back(5);

	std::cout << "List  contents: ";

	for (std::list	<int>::iterator it = mlist.begin(); it != mlist.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	return (0);
}
