/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:16:19 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 13:16:19 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_direction(t_minishell *minishell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">>"))
		{
			if (!ft_strcmp(args[i], ">"))
				minishell->fd_hl.change = 1;
			else if (!ft_strcmp(args[i], "<"))
				minishell->fd_hl.change = 2;
			else if (!ft_strcmp(args[i], ">>"))
				minishell->fd_hl.change = 3;
			return (i);
		}
		i++;
	}
}

// Devam edecek...
