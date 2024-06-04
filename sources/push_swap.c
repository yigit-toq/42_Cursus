/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:56:30 by ytop              #+#    #+#             */
/*   Updated: 2024/05/31 14:33:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/libft.h"

static void	ft_create_stack(t_manager *manager, char **args, int i, int j);
static void	ft_sort(t_manager *manager);

int	main(int argc, char **argv)
{
	t_manager	manager;

	argv++;
	ft_bzero(&manager, sizeof(t_manager));
	if (argc == 1)
		return (EXIT_SUCCESS);
	else if (argc == 2)
	{
		manager.args = ft_split(argv[0], ' ');
		ft_exit(&manager, 1, manager.args);
		if (!manager.args[0])
			ft_exit(&manager, 1, 0);
		ft_create_stack(&manager, manager.args, 0, 0);
	}
	else
		ft_create_stack(&manager, argv, 0, 0);
	ft_sort(&manager);
	ft_exit(&manager, 0, 0);
	return (EXIT_SUCCESS);
}

static void	ft_create_stack(t_manager *manager, char **args, int i, int j)
{
	while (args[manager->size_a])
		manager->size_a++;
	manager->a = ft_calloc(manager->size_a, sizeof(int));
	ft_exit(manager, 1, manager->a);
	manager->b = ft_calloc(manager->size_a, sizeof(int));
	ft_exit(manager, 1, manager->b);
	while (args[i])
	{
		manager->number = ft_strtrim(args[i], " ");
		ft_exit(manager, 1, manager->number);
		manager->a[i] = ps_atoi(manager, manager->number, 0, 1);
		free(manager->number);
		manager->number = 0;
		i++;
	}
	i = -1;
	while (++i < manager->size_a)
	{
		j = i;
		while (++j < manager->size_a)
		{
			if (manager->a[i] == manager->a[j])
				ft_exit(manager, 1, 0);
		}
	}
}

static void	ft_sort(t_manager *manager)
{
	if (sort_check(manager->a, manager->size_a))
		return ;
	if (manager->size_a == 2)
		swap_stack(manager, manager->a, manager->size_a, 1);
	else if (manager->size_a == 3)
		three_sort(manager);
	else if (manager->size_a <= 32)
		selection_sort(manager);
	else
	{
		stack_index(manager, manager->a, manager->size_a);
		radix_sort(manager);
	}
}

static void	ft_free(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (args[i])
			free(args[i]);
		i++;
	}
	if (args)
		free(args);
}

void	ft_exit(t_manager *manager, int type, void *ptr)
{
	if (ptr)
		return ;
	ft_free(manager->args);
	if (manager->a)
		free(manager->a);
	if (manager->b)
		free(manager->b);
	if (manager->number)
		free(manager->number);
	if (type)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
}
