/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:45:28 by ytop              #+#    #+#             */
/*   Updated: 2025/01/14 12:41:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEREPLACER_HPP
#define FILEREPLACER_HPP

#include <iostream>
#include <fstream>
#include <string>

class FileReplacer
{
	private:
		std::fstream	filePipe[2];
		std::string		filePath[2];
		std::string		srcString;
		std::string		rplString;

		std::string		replaceProcess(const std::string& line);

	public:
		FileReplacer (const std::string& path, const std::string& search, const std::string& replace);

		~FileReplacer();

		bool openFile(std::fstream &file, const std::string& path, std::ios::openmode mode);

		bool process ();
};
#endif
