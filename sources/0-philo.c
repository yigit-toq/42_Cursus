/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/03 19:15:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	eat(t_philo *philo);
static int	philo_control(t_philo *philo, int type);
static int	print_message(t_philo *philo, char *mesagge);

void	routine(t_philo *philo)
{
	if (philo->id % 2)
		ft_sleep(10);
	while (1)
	{
		eat(philo);
		if (philo_control(philo, 1))
			break ;
	}
	return ;
}

static int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&data->m_eat);
	print_message(philo, "is eating");
	philo->eat_last = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->arguments[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping");
	ft_sleep(data->arguments[3]);
	print_message(philo, "is thinking");
	philo_control(philo, 0);
	return (SUCCESS);
}

static int	philo_control(t_philo *philo, int type)
{
	t_data	*data;
	int		bool;

	data = philo->data;
	bool = FALSE;
	if (get_time() - philo->eat_last > philo->data->arguments[1] && type)
	{
		print_message(philo, "died");
		bool = TRUE;
	}
	if (!type)
	{
		if (philo->eat_count == philo->data->arguments[4])
			if (philo == &philo[philo->data->arguments[0] - 1])
				bool = TRUE;
	}
	if (bool == TRUE)
	{
		set_int(&philo->data->m_dead, &philo->data->s_dead, 1);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	print_message(t_philo *philo, char *mesagge)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	printf("%-6d %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	pthread_mutex_unlock(&data->m_print);
	if (get_int(&philo->data->m_dead, &philo->data->s_dead))
		return (FAILURE);
	return (SUCCESS);
}
