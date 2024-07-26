/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:39:10 by ytop              #+#    #+#             */
/*   Updated: 2024/07/26 18:14:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	long long			timer;
	static long long	start;
	static int			flag;
	struct timeval		time;

	gettimeofday(&time, NULL);
	timer = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (!flag)
	{
		start = timer;
		flag = 1;
	}
	return (timer - start);
}

int	ft_sleep(int time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(300);
	return (SUCCESS);
}

int	var_int(pthread_mutex_t *mutex, int *dest, int value, int type)
{
	pthread_mutex_lock(mutex);
	if (type == SET)
		*dest = value;
	else
		value = *dest;
	pthread_mutex_unlock(mutex);
	if (type == GET)
	{
		dest = &value;
		return (value);
	}
	return (SUCCESS);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	life_control(t_philo *philo, t_data *data)
{
	if (philo->eat_count == data->arguments[4]
		|| var_int(&data->m_dead, &data->p_dead, UNUSED, GET))
		return (FAILURE);
	else
		return (SUCCESS);
}
