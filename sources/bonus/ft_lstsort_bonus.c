/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:09:06 by ytop              #+#    #+#             */
/*   Updated: 2024/10/02 16:46:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **lst, int (*cmp)(char *, char *))
{
	t_list	*tmp;
	t_list	*node;
	void	*content;

	node = *lst;
	while (node)
	{
		tmp = node->next;
		while (tmp)
		{
			if (cmp(node->content, tmp->content) > 0)
			{
				content = node->content;
				node->content = tmp->content;
				tmp->content = content;
			}
			tmp = tmp->next;
		}
		node = node->next;
	}
}
