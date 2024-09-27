/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:07:10 by ytop              #+#    #+#             */
/*   Updated: 2024/09/28 01:07:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_arg(t_minishell *minishell)
{
	int		token_count;
	char	***args;

	token_count = ft_lstsize(minishell->tokens);
	args = allocate_args(token_count);
	if (!args)
		return (FAILURE);
	minishell->args_with_quotes = allocate_args(token_count);
	if (!minishell->args_with_quotes)
		return (free_args(args), FAILURE);
	if (process_tokens(minishell, args) == FAILURE)
		return (free_args(args), FAILURE);
	minishell->args = args;
	return (SUCCESS);
}

static char	***allocate_args(int count)
{
	char	***args;

	args = ft_calloc(1, sizeof(char **) * (count + 1));
	if (!args)
		perror("ft_calloc");
	return (args);
}

static int	process_tokens(t_minishell *minishell, char ***args)
{
	t_list	*tokens;
	int		i;

	tokens = minishell->tokens;
	i = 0;
	while (tokens)
	{
		if (handle_token(tokens, args, minishell->args_with_quotes, i))
			return (FAILURE);
		i++;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
