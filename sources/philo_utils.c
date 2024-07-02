/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/02 20:43:18 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void	eat(t_philo *philo);

void	routine(t_philo *philo)
{
	if (philo->id % 2)
		usleep(100);
	while (!philo->data->s_dead)
	{
		eat(philo);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork);
	print_message(philo, "has taken a fork");
	philo->eat_last = get_time();
	philo->eat_count++;
	if (philo->eat_last - philo->data->arguments[1] > 0)
	{
		print_message(philo, "died");
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return ;
	}
	print_message(philo, "is eating");
	usleep(philo->data->arguments[1] * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	print_message(philo, "is sleeping");
	usleep(philo->data->arguments[2] * 1000);
	print_message(philo, "is thinking");
	return ;
}

int	print_message(t_philo *philo, char *mesagge)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print);
	printf("%-6d %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	pthread_mutex_unlock(&data->print);
	return (SUCCESS);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	set_get_int(pthread_mutex_t *mutex, int *dest, int value, int type)
{
	pthread_mutex_lock(mutex);
	if (type == SET)
		*dest = value;
	else
		value = *dest;
	pthread_mutex_unlock(mutex);
	if (type == GET)
		dest = &value;
	return ;
}
