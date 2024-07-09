/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/09 19:45:14 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	loop(t_philo *philo, t_data *data);
static int	print_message(t_philo *philo, char *mesagge, char *color);

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_ready);
	pthread_mutex_unlock(&philo->data->m_ready);
	if (philo->data->p_count != philo->data->arguments[0] - 1)
		return ;
	if (philo->data->arguments[0] == 1)
	{
		print_message(philo, FORK, YELLOW);
		ft_sleep(philo->data->arguments[1]);
		print_message(philo, DEAD, RED);
		return ;
	}
	if (!(philo->id % 2))
		ft_sleep(philo->data->arguments[1] / 4);
	while (!get_int(&philo->data->m_dead, &philo->data->s_dead))
	{
		if (loop(philo, philo->data) == 0)
			break ;
	}
	return ;
}

static int	loop(t_philo *philo, t_data *data)
{
	if (philo->eat_count == data->arguments[4] && data->arguments[4])
		return (FAILURE);
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, FORK, YELLOW);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, FORK, YELLOW);
	pthread_mutex_lock(&data->m_eat);
	print_message(philo, EAT, GREEN);
	philo->eat_last = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->arguments[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, SLEEP, BLUE);
	ft_sleep(data->arguments[3]);
	print_message(philo, THINK, PURPLE);
	return (SUCCESS);
}

static int	print_message(t_philo *philo, char *mesagge, char *color)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	if ((philo->eat_count == data->arguments[4] && data->arguments[4])
		|| get_int(&data->m_dead, &data->s_dead))
		return (pthread_mutex_unlock(&data->m_print), FAILURE);
	printf("%s", color);
	printf("%-6lld %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	printf("%s", END);
	pthread_mutex_unlock(&data->m_print);
	return (SUCCESS);
}

int	thread_create(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	pthread_mutex_lock(&data->m_ready);
	while (i < data->arguments[0])
	{
		if (pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]))
			break ;
		data->p_count = i++;
	}
	pthread_mutex_unlock(&data->m_ready);
	death_control(data);
	i = 0;
	while (i < data->arguments[0])
	{
		if (pthread_join(philo[i].thread, NULL))
			break ;
		i++;
	}
	return (FAILURE);
}

int	death_control(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	if (data->p_count != data->arguments[0] - 1)
		return (FAILURE);
	while (i < data->arguments[0])
	{
		pthread_mutex_lock(&data->m_eat);
		if (get_time() - philo[i].eat_last >= data->arguments[1])
		{
			if (philo[i].eat_count == data->arguments[4] && data->arguments[4])
				return (pthread_mutex_unlock(&data->m_eat), FAILURE);
			print_message(&philo[i], DEAD, RED);
			set_int(&data->m_dead, &data->s_dead, 1);
			pthread_mutex_unlock(&data->m_eat);
			return (FAILURE);
		}
		pthread_mutex_unlock(&data->m_eat);
		if (i == data->arguments[0] - 1)
			i = 0;
		i++;
	}
	return (SUCCESS);
}
