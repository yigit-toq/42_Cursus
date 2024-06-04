/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:29:18 by ytop              #+#    #+#             */
/*   Updated: 2024/05/31 14:57:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_manager
{
	char	**args;
	int		*a;
	int		*b;
	int		size_a;
	int		size_b;
	char	*number;
}			t_manager;

int		sort_check(int *stack, int size);

int		ps_atoi(t_manager *manager, char *str, long int result, int sign);

void	selection_sort(t_manager *manager);

void	radix_sort(t_manager *manager);

void	three_sort(t_manager *manager);

void	stack_index(t_manager *manager, int *stack, int size);

void	swap_stack(t_manager *manager, int *stack, int size, int flag);

void	rotate_stack(t_manager *manager, int *stack, int size, int flag);
void	rev_rotate_stack(t_manager *manager, int *stack, int size, int flag);

void	push_stack(t_manager *manager, int *stack1, int *stack2, int *size1);

void	double_process(t_manager *manager, int action);

void	ft_exit(t_manager *manager, int type, void *ptr);
#endif