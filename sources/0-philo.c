/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/03 16:30:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

void	eat(t_philo *philo);

void	routine(t_philo *philo)
{
	if (philo->id % 2)
		ft_usleep(10);
	while (1)
	{
		eat(philo);
	}
	return ;
}

void	eat(t_philo *philo)
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
	ft_usleep(data->arguments[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping");
	ft_usleep(data->arguments[3]);
	print_message(philo, "is thinking");
	if (philo->eat_count == data->arguments[4]
		&& philo == &data->philo[data->arguments[0] - 1])
	{
		pthread_mutex_lock(&data->m_dead);
		data->s_dead = 1;
		pthread_mutex_unlock(&data->m_dead);
	}
}

int	print_message(t_philo *philo, char *mesagge)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	if (data->s_dead)
	{
		pthread_mutex_unlock(&data->m_print);
		return (FAILURE);
	}
	printf("%-6d %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	pthread_mutex_unlock(&data->m_print);
	return (SUCCESS);
}
