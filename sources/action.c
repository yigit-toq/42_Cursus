/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:54:40 by ytop              #+#    #+#             */
/*   Updated: 2024/05/23 00:54:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/libft.h"

void	swap_stack(t_manager *manager, int *stack, int size, int flag)
{
	int	tmp;

	if (size > 1)
	{
		tmp = stack[0];
		stack[0] = stack[1];
		stack[1] = tmp;
		if (flag)
		{
			if (stack == manager->a)
				ft_printf("sa\n");
			else
				ft_printf("sb\n");
		}
	}
}

void	rotate_stack(t_manager *manager, int *stack, int size, int flag)
{
	int	tmp;
	int	i;

	if (size > 1)
	{
		tmp = stack[0];
		i = 0;
		while (i < size - 1)
		{
			stack[i] = stack[i + 1];
			i++;
		}
		stack[i] = tmp;
		if (flag)
		{
			if (stack == manager->a)
				ft_printf("ra\n");
			else
				ft_printf("rb\n");
		}
	}
}

void	rev_rotate_stack(t_manager *manager, int *stack, int size, int flag)
{
	int	tmp;
	int	i;

	if (size > 1)
	{
		tmp = stack[size - 1];
		i = size - 1;
		while (i > 0)
		{
			stack[i] = stack[i - 1];
			i--;
		}
		stack[i] = tmp;
		if (flag)
		{
			if (stack == manager->a)
				ft_printf("rra\n");
			else
				ft_printf("rrb\n");
		}
	}
}

void	push_stack(t_manager *manager, int *stack1, int *stack2, int *size1)
{
	int	*size2;
	int	i;

	if (stack1 == manager->a)
		size2 = &manager->size_b;
	else
		size2 = &manager->size_a;
	if (*size1 > 0)
	{
		i = *size2 + 1;
		while (--i > 0)
			stack2[i] = stack2[i - 1];
		stack2[0] = stack1[0];
		*size1 -= 1;
		i = -1;
		while (++i < *size1)
			stack1[i] = stack1[i + 1];
		*size2 += 1;
		if (stack2 == manager->a)
			ft_printf("pa\n");
		else
			ft_printf("pb\n");
	}
}

void	double_process(t_manager *manager, int action)
{
	if (action == 0)
	{
		swap_stack(manager, manager->a, manager->size_a, 0);
		swap_stack(manager, manager->b, manager->size_b, 0);
		ft_printf("ss\n");
	}
	else if (action == 1)
	{
		rotate_stack(manager, manager->a, manager->size_a, 0);
		rotate_stack(manager, manager->b, manager->size_b, 0);
		ft_printf("rr\n");
	}
	else if (action == 2)
	{
		rev_rotate_stack(manager, manager->a, manager->size_a, 0);
		rev_rotate_stack(manager, manager->b, manager->size_b, 0);
		ft_printf("rrr\n");
	}
}
