/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:18:52 by ytop              #+#    #+#             */
/*   Updated: 2025/07/22 21:54:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVCOMMAND_HPP
#define PRIVCOMMAND_HPP

# include "CommandHandler.hpp"

class Server;

class PrivCommand : public CommandHandler
{
	private:
		Server& _server; // Sunucuya referans

	public:
		PrivCommand(Server& server);
		~PrivCommand();

		void Execute(Client* sender, const Message& msg);

	private:
		PrivCommand(const PrivCommand& other);
		PrivCommand& operator=(const PrivCommand& other);
};

#endif
