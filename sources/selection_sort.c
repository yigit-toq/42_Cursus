/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:54 by ytop              #+#    #+#             */
/*   Updated: 2024/05/28 00:20:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	r_or_rr(t_manager *manager, int min_value, int min_index);
static int	find_min_index(int *stack, int size);

void	selection_sort(t_manager *manager)
{
	int	index;
	int	min_index;
	int	min_value;
	int	size;

	index = 0;
	size = manager->size_a;
	while (index < size && !sort_check(manager->a, manager->size_a))
	{
		min_index = find_min_index(manager->a, manager->size_a);
		min_value = manager->a[min_index];
		if (manager->a[0] != min_value && manager->size_a > 1)
			r_or_rr(manager, min_value, min_index);
		if (!sort_check(manager->a, manager->size_a))
			push_stack(manager, manager->a, manager->b, &manager->size_a);
		index++;
	}
	while (manager->size_b > 0)
		push_stack(manager, manager->b, manager->a, &manager->size_b);
}

static void	r_or_rr(t_manager *m, int min_value, int min_index)
{
	if (min_index >= m->size_a / 2 + m->size_a % 2)
	{
		while (m->a[0] != min_value && !sort_check(m->a, m->size_a))
			rev_rotate_stack(m, m->a, m->size_a, 1);
	}
	else
	{
		while (m->a[0] != min_value && !sort_check(m->a, m->size_a))
			rotate_stack(m, m->a, m->size_a, 1);
	}
}

static int	find_min_index(int *stack, int size)
{
	int	i;
	int	min;
	int	index;

	i = 0;
	index = 0;
	min = stack[0];
	while (i < size)
	{
		if (stack[i] < min)
		{
			min = stack[i];
			index = i;
		}
		i++;
	}
	return (index);
}
