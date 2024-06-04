/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:38 by ytop              #+#    #+#             */
/*   Updated: 2024/05/24 14:06:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/libft.h"

static int	get_min_index(int *visited, int *stack, int size)
{
	int	min_index;
	int	min_value;
	int	i;

	min_index = -1;
	min_value = 0;
	i = 0;
	while (i < size)
	{
		if (!visited[i] && (min_index == -1 || stack[i] < min_value))
		{
			min_index = i;
			min_value = stack[i];
		}
		i++;
	}
	return (min_index);
}

void	stack_index(t_manager *manager, int *stack, int size)
{
	int	*visited;
	int	min_index;
	int	index;

	visited = ft_calloc(size, sizeof(int));
	ft_exit(manager, 1, visited);
	index = 0;
	min_index = get_min_index(visited, stack, size);
	while (min_index != -1)
	{
		stack[min_index] = index++;
		visited[min_index] = 1;
		min_index = get_min_index(visited, stack, size);
	}
	free(visited);
}

void	three_sort(t_manager *manager)
{
	if (manager->a[0] > manager->a[1])
	{
		swap_stack(manager, manager->a, manager->size_a, 1);
	}
	if (manager->a[1] > manager->a[2])
	{
		rev_rotate_stack(manager, manager->a, manager->size_a, 1);
		three_sort(manager);
	}
}

int	sort_check(int *stack, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (stack[i] > stack[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ps_atoi(t_manager *manager, char *str, long int result, int sign)
{
	int	i;

	i = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		ft_exit(manager, 1, 0);
	while (*str == '0')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_exit(manager, 1, 0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result * sign > INT_MAX || result * sign < INT_MIN || i > 10)
		ft_exit(manager, 1, 0);
	return (result * sign);
}
