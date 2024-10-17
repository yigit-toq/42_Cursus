/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:44:12 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 16:48:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdbool.h"

static bool	free_delone(void *address);

void	*galloc(size_t size)
{
	void	*address;

	address = addgarbage(malloc(size));
	return (address);
}

void	*addgarbage(void *address)
{
	t_list	**collector;
	t_list	*tmp;

	if (!address)
		return (0);
	if (!GARBAGE_COLLECTOR)
		return (address);
	collector = getgarbage();
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	tmp->next = 0;
	tmp->prev = 0;
	tmp->content = address;
	if (*collector)
	{
		tmp->next = *collector;
		tmp->next->prev = tmp;
		*collector = tmp;
	}
	else
		*collector = tmp;
	return (tmp->content);
}

void	clear_garbage(void)
{
	t_list	**collector;
	t_list	*todel;
	t_list	*tmp;

	collector = getgarbage();
	todel = *collector;
	while (todel)
	{
		free(todel->content);
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	*collector = 0;
}

void	gfree(void *address)
{
	if (address && !GARBAGE_COLLECTOR)
		free(address);
	else if (!address || !GARBAGE_COLLECTOR)
		return ;
	else if (!free_delone(address))
		free(address);
}

static bool	free_delone(void *address)
{
	t_list	*node;

	node = *getgarbage();
	while (node && address)
	{
		if (node->content == address)
		{
			if (node->prev)
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
			else
			{
				node->next->prev = 0;
				*getgarbage() = node->next;
			}
			free(node->content);
			free(node);
			return (true);
		}
		node = node->next;
	}
	return (false);
}
