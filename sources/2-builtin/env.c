/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:16:27 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 17:16:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_list(char *env[])
{
	t_minishell	*minishell;
	int			i;

	i = 0;
	minishell = get_minishell();
	minishell->env = ft_lstnew(ft_strdup(env[i]));
	while (env[++i])
	{
		ft_lstadd_back(&minishell->env, ft_lstnew(ft_strdup(env[i])));
	}
}

static char	*get_value(char *line);

void	get_env(t_minishell *shell, char **result, char **str, int *i)
{
	t_list	*env_value;
	char	*new_result;
	char	*env_var;
	char	*tmp;
	int		v_st;

	v_st = ++(*i);
	while ((*str)[*i] && ft_isalnum((*str)[*i]))
		(*i)++;
	env_var = ft_substr(*str, v_st, (*i) - v_st);
	env_value = search_env(shell, env_var);
	gfree(env_var);
	if (!env_value)
		return ;
	tmp = get_value(env_value->content);
	new_result = ft_strjoin(*result, tmp);
	gfree(tmp);
	gfree(*result);
	*result = new_result;
}

static int	get_key(char *line)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '=')
		j++;
	return (j);
}

static char	*get_value(char *line)
{
	char	*value;
	int		i;

	if (!line)
		return (NULL);
	i = get_key(line);
	if (!line[i])
		return (NULL);
	value = ft_strdup(line + i + 1);
	return (value);
}

t_list	*search_env(t_minishell *minishell, char *key)
{
	t_list	*cur_env;
	char	*env_key;

	if (key == NULL || ft_strlen(key) == 0)
		return (NULL);
	cur_env = minishell->env;
	while (cur_env)
	{
		env_key = ft_substr(cur_env->content, 0, get_key(cur_env->content));
		if (!ft_strcmp(env_key, key))
		{
			gfree(env_key);
			return (cur_env);
		}
		gfree(env_key);
		cur_env = cur_env->next;
	}
	return (NULL);
}
