/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:48:33 by abakirca          #+#    #+#             */
/*   Updated: 2024/07/08 13:48:40 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdbool.h"

static bool	free_from_ll(void *address);

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
	else if (!free_from_ll(address))
		free(address);
}

static bool	free_from_ll(void *address)
{
	t_list	*todel;

	todel = *getgarbage();
	while (todel && address)
	{
		if (todel->content == address)
		{
			if (todel->prev)
			{
				todel->prev->next = todel->next;
				todel->next->prev = todel->prev;
			}
			else
			{
				todel->next->prev = 0;
				*getgarbage() = todel->next;
			}
			free(todel->content);
			free(todel);
			return (true);
		}
		todel = todel->next;
	}
	return (false);
}
