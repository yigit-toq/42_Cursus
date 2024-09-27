/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:42:03 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 14:42:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(void)
{
	t_minishell	*minishell;
	char		*line;
	int			quote;

	minishell = get_minishell();
	line = ft_strtrim(minishell->line, " ");
	if (ft_strcmp(line, "") == 0)
		return (gfree(line), FAILURE);
	quote = check_quote(line, ft_strlen(line));
	if (quote)
	{
		gfree(line);
		minishell->value.exit_code = 2;
		return (ft_dprintf(STD_ERROR, SYNTAX_ERR " `%c\'\n", quote), FAILURE);
	}
	return (SUCCESS);
}

//pipe_control eklenecek

int	check_quote(char *line, int value)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < value)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	return ((int)quote);
}
