/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:32:47 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 00:32:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_minishell *minishell)
{
	if (!minishell->value.pipe_count)
		return (single_command(minishell));
	else
		return (multiple_command(minishell));
	return (FAILURE);
}

static int	single_command(t_minishell *minishell)
{
	t_parser	*parser;
	char		**cmd;
	int			i;

	i = 0;
	parser = minishell->parser;
}
