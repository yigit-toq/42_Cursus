/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:27:30 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 18:27:30 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_dollar(t_minishell *shell, char **result, int *i);

static int	empty_dollar(char *line);

void	dollar(t_minishell *shell)
{
	char	*result;
	char	quote;
	int		i;

	if (empty_dollar(shell->line))
		return ;
	quote = 0;
	result = ft_strdup("");
	while (shell->line[i])
	{
		if (!quote && (shell->line[i] == '\'' || shell->line[i] == '\"'))
			quote = shell->line[i];
		else if (quote && quote == shell->line[i])
			quote = 0;
		if (quote == '\'' || (!quote && shell->line[i] == '\''))
			result = strjoin_char(result, shell->line[i++]);
		else
			replace_dollar(shell, &result, &i);
	}
	gfree(shell->line);
	shell->line = result;
}

static int	empty_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!ft_isalnum(line[i + 1])
				&& line[i + 1] != '?'
				&& line[i + 1] != '$'
				&& line[i + 1] != '\''
				&& line[i + 1] != '\"')
				break ;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

// Düzenleme yapılabilir

static void	replace_dollar(t_minishell *shell, char **result, int *i)
{
	char	*tmp;
	char	*str;

	str = shell->line;
	if (str[*i] == '$' && str[*i + 1] == '\"')
	{
		tmp = *result;
		*result = strjoin_char(tmp, str[(*i)++]);
	}
	else if (str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '?')
		get_ext_code(shell, result, i);
	else if (str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] != '$')
		get_env(shell, result, &str, i);
	else
	{
		tmp = *result;
		*result = strjoin_char(tmp, str[(*i)++]);
	}
}
