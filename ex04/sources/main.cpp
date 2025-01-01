/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:16:59 by ytop              #+#    #+#             */
/*   Updated: 2025/01/01 22:09:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstddef>
#include <fstream>

#define TRUE    1
#define FALSE   0

int open_file(std::fstream &file, const char *path, int type);

int main(int argc, char **argv)
{
	std::fstream	files[2];
	std::string		outName;
	std::string		oldStr;
	std::string		read;
	std::string		line;
	size_t			spos;

	if (argc != 4)
	{
		std::cerr << "Invalid Input" << std::endl;
		return (1);	
	}
	if (!open_file(files[0], argv[1], 0))
		return (1);

	oldStr = argv[2];
	outName = argv[1];
	outName.append(".replace");

	if (!open_file(files[1], outName.c_str(), 1))
		return (1);

	while (std::getline(files[0], read))
	{
		spos = 0;
		line.clear();
		while ((spos = read.find(oldStr, spos)) != std::string::npos)
		{
			line.append(read.substr(0, spos));
			line.append(argv[3]);
			spos += oldStr.length();
			read = read.substr(spos);
			spos = 0;
		}
		line.append(read);
		files[1] << line << std::endl;
	}
	files[0].close();
	files[1].close();
	return (0);
}

int open_file(std::fstream &file, const char *path, int type)
{
    if (type)
        file.open(path, std::ios::out);
    else
        file.open(path, std::ios::in);

    if (file.is_open() == FALSE)
    {
        std::cerr << "File doesn't exist" << std::endl;
        return (FALSE);
    }
    return (TRUE);
}
