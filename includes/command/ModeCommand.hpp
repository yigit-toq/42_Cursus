/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:09:44 by ytop              #+#    #+#             */
/*   Updated: 2025/07/26 04:01:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "CommandHandler.hpp"

class Server;

class ModeCommand : public CommandHandler
{
	private:
		Server&					_server;

	private:
		ModeCommand				(const ModeCommand& other);
		ModeCommand& operator=	(const ModeCommand& other);

	public:
		 ModeCommand			(Server& server);
		~ModeCommand			();

		void Execute			(Client* sender, const Message& msg);

		bool IsModeWithParameter(char mode)
		{
			return (mode == 'o' || mode == 'l' || mode == 'k');
		}

		std::vector<std::pair<char, char>> ParseModeString(const std::string& mode_string)
		{
			std::vector<std::pair<char, char>>	parsed_modes;

			char current_sign = '+';

			for (size_t i = 0; i < mode_string.length(); ++i)
			{
				char c = mode_string[i];

				if (c == '+' || c == '-')
				{
					current_sign = c;
				}
				else
				{
					parsed_modes.push_back(std::make_pair(current_sign, c));
				}
			}
			return (parsed_modes);
		}
};

#endif
