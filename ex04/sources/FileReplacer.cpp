/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:47:59 by ytop              #+#    #+#             */
/*   Updated: 2025/01/14 12:40:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileReplacer.hpp"

FileReplacer::FileReplacer(const std::string& path, const std::string& search, const std::string& replace)
{
	this->filePath[0] = path;
	this->filePath[1] = path + ".replace";

	this->srcString = search;
	this->rplString = replace;

	std::cout << "Constructor" << std::endl;
}

FileReplacer::~FileReplacer()
{
	std::cout << "Destructor!" << std::endl;
}

bool	FileReplacer::openFile(std::fstream &file, const std::string& path, std::ios::openmode mode)
{
	file.open(path.c_str(), mode);
	if (!file.is_open())
	{
		std::cerr << "File doesn't exist" << std::endl;
		return (false);
	}
	return (true);
}

bool	FileReplacer::process()
{
	std::string	line;

	if (openFile(filePipe[0], filePath[0], std::ios::in ) == false)
	{
		return (false);
	}
	if (openFile(filePipe[1], filePath[1], std::ios::out) == false)
	{
		filePipe[0].close();
		return (false);
	}
	while (std::getline(filePipe[0], line))
	{
		filePipe[1] << replaceProcess(line) << std::endl;
	}
	filePipe[0].close();
	filePipe[1].close();
	return (true);
}

std::string	FileReplacer::replaceProcess(const std::string& line)
{
	std::string	result;
	size_t		start;
	size_t		found;

	start = 0;
	while ((found = line.find(srcString, start)) != std::string::npos)
	{
		result.append(line, start, found - start);
		result.append(rplString);
		start = found + srcString.length();
	}
	result.append(line, start, std::string::npos);
	return (result);
}
