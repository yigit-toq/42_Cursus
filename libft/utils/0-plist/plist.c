/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:02:04 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 14:02:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_parser	*ft_parser_new(char **args, char **args_with_quote)
{
	t_parser	*new;

	new = calloc(1, sizeof(t_parser));
	if (!new)
		return (NULL);
	new->args_quote = args_with_quote;
	new->args = args;
	new->next = NULL;
	return (new);
}

void	ft_parser_addback(t_parser **lst, t_parser *new)
{
	t_parser	*node;

	node = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
}
