/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/04 09:53:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	loop(t_philo *philo);
static int	print_message(t_philo *philo, char *mesagge, char *color);

void	routine(t_philo *philo)
{
	if (!(philo->id % 2))
		ft_sleep(10);
	while (1)
	{
		loop(philo);
	}
	return ;
}

static int	loop(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(&data->m_eat);
	print_message(philo, "is eating", GREEN);
	philo->eat_last = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->arguments[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping", BLUE);
	ft_sleep(data->arguments[3]);
	print_message(philo, "is thinking", PURPLE);
	return (SUCCESS);
}

static int	print_message(t_philo *philo, char *mesagge, char *color)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	printf("%s", color);
	printf("%-6d %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	printf("%s", END);
	pthread_mutex_unlock(&data->m_print);
	if (get_int(&philo->data->m_dead, &philo->data->s_dead))
		return (FAILURE);
	return (SUCCESS);
}

int	death_control(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (1)
	{
		if (get_time() - philo->eat_last > data->arguments[1])
		{
			print_message(philo, "died", RED);
			set_int(&data->m_dead, &data->s_dead, 1);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
