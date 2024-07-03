/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:10 by ytop              #+#    #+#             */
/*   Updated: 2024/07/03 14:44:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <unistd.h>

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return ;
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
