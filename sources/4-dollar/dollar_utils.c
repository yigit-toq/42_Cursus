/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:50:28 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 22:50:28 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ext_code(t_minishell *shell, char **result, int *i)
{
	int		index;
	char	*nbr;
	char	*tmp;

	nbr = ft_itoa(shell->value.exit_code);
	index = 0;
	(*i) += 2;
	while (nbr[index])
	{
		tmp = *result;
		*result = strjoin_char(tmp, nbr[index++]);
	}
	gfree(nbr);
}

char	*strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(s1);
	if (!s1)
	{
		result = ft_calloc(2, sizeof(char));
		if (!result)
			return (NULL);
	}
	else
	{
		result = ft_calloc(len + 2, sizeof(char));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1, len + 1);
		gfree(s1);
	}
	result[len] = c;
	return (result);
}
