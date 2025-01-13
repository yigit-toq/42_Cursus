/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:45:28 by ytop              #+#    #+#             */
/*   Updated: 2025/01/13 20:50:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <fstream>

class FileHandler
{
	private:
		std::fstream	files[2];
		std::string		outName;
		std::string		oldStr;
		std::string		read;
		std::string		line;

	public:
		FileHandler ();

		~FileHandler();

		bool openFile(std::fstream &file, const char *path, int type);

		bool readFile(int index);
};

#endif