/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:10 by ytop              #+#    #+#             */
/*   Updated: 2024/07/15 17:53:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_sleep(int time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (SUCCESS);
}

int	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
	return (SUCCESS);
}

int	get_int(pthread_mutex_t *mutex, int *dest)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *dest;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	ft_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arguments[0])
	{
		kill(*data->philo[i].pid, 9);
		i++;
	}
}
