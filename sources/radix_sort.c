/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:03:59 by ytop              #+#    #+#             */
/*   Updated: 2024/05/24 17:03:59 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	radix_sort_utils(t_manager *manager, int i);
static int	get_max_bits(t_manager *manager);

void	radix_sort(t_manager *manager)
{
	int	i;
	int	j;
	int	size;
	int	max_bits;

	max_bits = get_max_bits(manager);
	i = 0;
	while (i < max_bits && !sort_check(manager->a, manager->size_a))
	{
		size = manager->size_a;
		j = 0;
		while (j < size && !sort_check(manager->a, manager->size_a))
		{
			if ((manager->a[0] >> i) & 1)
				rotate_stack(manager, manager->a, manager->size_a, 1);
			else
				push_stack(manager, manager->a, manager->b, &manager->size_a);
			j++;
		}
		i++;
		if (i <= max_bits)
			radix_sort_utils(manager, i);
	}
	while (manager->size_b > 0)
		push_stack(manager, manager->b, manager->a, &manager->size_b);
}

static void	radix_sort_utils(t_manager *manager, int i)
{
	int	j;
	int	size;

	j = 0;
	size = manager->size_b;
	while (j < size)
	{
		if ((manager->b[0] >> i) & 1)
			push_stack(manager, manager->b, manager->a, &manager->size_b);
		else
			rotate_stack(manager, manager->b, manager->size_b, 1);
		j++;
	}
}

static int	get_max_bits(t_manager *manager)
{
	int	max_bits;
	int	max;
	int	i;

	max = manager->a[0];
	i = 1;
	while (i < manager->size_a)
	{
		if (manager->a[i] > max)
		{
			max = manager->a[i];
		}
		i++;
	}
	max_bits = 0;
	while (max >> max_bits)
		max_bits++;
	return (max_bits);
}
