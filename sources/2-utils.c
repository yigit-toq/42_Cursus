/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:10 by ytop              #+#    #+#             */
/*   Updated: 2024/07/04 09:18:38 by ytop             ###   ########.fr       */
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

int	ft_sleep(int time)
{
	int	start;

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

// void	v_int(pthread_mutex_t *mutex, int *dest, int value, int type)
// {
// 	pthread_mutex_lock(mutex);
// 	if (type == SET)
// 		*dest = value;
// 	else
// 		value = *dest;
// 	pthread_mutex_unlock(mutex);
// 	if (type == GET)
// 		dest = &value;
// 	return ;
// }
