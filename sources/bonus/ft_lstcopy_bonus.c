/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:59:26 by ytop              #+#    #+#             */
/*   Updated: 2024/10/04 15:35:58 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*new_lst;
	t_list	*current;
	t_list	*new_node;
	t_list	*temp;

	new_lst = NULL;
	current = lst;
	while (current)
	{
		new_node = ft_lstnew(current->content);
		if (!new_node)
		{
			while (new_lst)
			{
				temp = new_lst;
				new_lst = new_lst->next;
				gfree(temp->content);
				gfree(temp);
			}
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		current = current->next;
	}
	return (new_lst);
}
