/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/06/28 18:12:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void	eat(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->left_fork);
	print_message(ph, "has taken a fork");
	pthread_mutex_lock(&ph->right_fork);
	print_message(ph, "has taken a fork");
	ph->eat_last = get_time();
	ph->eat_count++;
	print_message(ph, "is eating");
	usleep(ph->data->arguments[1] * 1000);
	pthread_mutex_unlock(&ph->left_fork);
	pthread_mutex_unlock(&ph->right_fork);
	print_message(ph, "is sleeping");
	usleep(ph->data->arguments[2] * 1000);
	print_message(ph, "is thinking");
}

int	print_message(t_philo *philo, char *mesagge)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mutex);
	if (!philo->is_dead)
		printf("%-6d %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	pthread_mutex_unlock(&data->mutex);
	return (SUCCESS);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
