/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:36:20 by ytop              #+#    #+#             */
/*   Updated: 2024/08/08 14:15:02 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	node = *lst;
	if (!lst)
		return ;
	while (node != 0)
	{
		node = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = node;
	}
}
