/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:27 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 00:52:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_list(char *env[])
{
	t_minishell	*minishell;
	int			i;

	minishell = get_minishell();
	i = 0;
	minishell->env = ft_lstnew(ft_strdup(env[i]));
	while (env[++i])
	{
		ft_lstadd_back(&minishell->env, ft_lstnew(ft_strdup(env[i])));
	}
}
