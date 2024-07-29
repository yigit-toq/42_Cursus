/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/29 13:48:31 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

static int	loop(t_philo *philo, t_data *data);
static int	print_message(t_philo *philo, char *mesagge, char *color);

int	thread_create(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	if (data->p_dead)
		return (SUCCESS);
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

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_ready);
	pthread_mutex_unlock(&philo->data->m_ready);
	if (philo->data->p_count != philo->data->arguments[0] - 1)
		return (NULL);
	if (philo->data->arguments[0] == 1)
	{
		print_message(philo, FORK, YELLOW);
		ft_sleep(philo->data->arguments[1]);
		print_message(philo, DEAD, RED);
		return (NULL);
	}
	if (!(philo->id % 2))
		ft_sleep(philo->data->arguments[2]);
	while (!var_int(&philo->data->m_dead, &philo->data->p_dead, UNUSED, GET))
	{
		if (!loop(philo, philo->data))
			break ;
	}
	return (NULL);
}

static int	loop(t_philo *philo, t_data *data)
{
	if (!life_control(philo, data))
		return (FAILURE);
	pthread_mutex_lock(philo->left_fork);
	if (!print_message(philo, FORK, YELLOW))
		return (pthread_mutex_unlock(philo->left_fork), FAILURE);
	pthread_mutex_lock(philo->right_fork);
	if (!print_message(philo, FORK, YELLOW))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), FAILURE);
	if (!print_message(philo, EAT, GREEN))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), FAILURE);
	pthread_mutex_lock(&data->m_eat);
	philo->eat_last = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->arguments[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!print_message(philo, SLEEP, BLUE))
		return (FAILURE);
	ft_sleep(data->arguments[3]);
	if (!print_message(philo, THINK, PURPLE))
		return (FAILURE);
	return (SUCCESS);
}

static int	print_message(t_philo *philo, char *mesagge, char *color)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	if (!life_control(philo, data))
		return (pthread_mutex_unlock(&data->m_print), FAILURE);
	if (!ft_strcmp(mesagge, DEAD))
		var_int(&data->m_dead, &data->p_dead, TRUE, SET);
	printf("|%s %6lld %s|", YELLOW, get_time(), END);
	printf("%s %3d %s", BOLD, philo->id, END);
	printf("|%s %s %s|\n", color, mesagge, END);
	pthread_mutex_unlock(&data->m_print);
	return (SUCCESS);
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
			if (philo[i].eat_count == data->arguments[4])
				return (pthread_mutex_unlock(&data->m_eat), FAILURE);
			print_message(&philo[i], DEAD, RED);
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
