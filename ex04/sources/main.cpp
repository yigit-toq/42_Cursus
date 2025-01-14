/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:24:11 by ytop              #+#    #+#             */
/*   Updated: 2025/01/14 12:44:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileReplacer.hpp"

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <search_string> <replace_string>" << std::endl;
		return (1);
	}
	FileReplacer	replacer(argv[1], argv[2], argv[3]);
	if (!replacer.process())
	{
		return (1);
	}
	std::cout << "File processing complete. Output written to " << argv[1] << ".replace" << std::endl;
	return (0);
}
