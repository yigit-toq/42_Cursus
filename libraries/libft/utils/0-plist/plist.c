/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:02:04 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 16:53:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_parser	*ft_parser_new(char **args)
{
	t_parser	*new;

	new = ft_calloc(1, sizeof(t_parser));
	if (!new)
		return (NULL);
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

void	ft_parser_delone(t_parser *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->args);
	gfree(lst);
}

void	ft_parser_clear(t_parser **lst, void (*del)(void *))
{
	t_parser	*node;

	if (!lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		ft_parser_delone(*lst, del);
		*lst = node;
	}
	*lst = 0;
}
