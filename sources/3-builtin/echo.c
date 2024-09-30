/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:34:21 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 23:34:21 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	flag_index;
	int	arg_index;
	int	newline;

	arg_index = 1;
	newline = 1;
	while (args[arg_index] && args[arg_index][0] == '-' && args[arg_index][1] == 'n')
	{
		flag_index = 1;
		while (args[arg_index][flag_index] == 'n')
			flag_index++;
		if (args[arg_index][flag_index] != '\0')
			break ;
		newline = 0;
		arg_index++;
	}
	while (args[arg_index])
	{
		ft_dprintf(STD_OUTPUT, "%s", args[arg_index]);
		if (args[arg_index + 1])
			ft_dprintf(STD_OUTPUT, " ");
		arg_index++;
	}
	if (newline)
		ft_dprintf(STD_OUTPUT, "\n");
}
