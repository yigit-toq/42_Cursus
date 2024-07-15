/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:08:22 by ytop              #+#    #+#             */
/*   Updated: 2024/07/15 15:18:29 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	arg_control(t_data *data, char **argv);
static int	init_philo(t_data *data);
static int	init_fork(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		error_control(&data, FAILURE, NOTAGR, -1);
	else if (argc == 6 && argv[5][0] == '0')
		return (EXIT_FAILURE);
	data.s_time = get_time();
	error_control(&data, arg_control(&data, argv + 1), NOTNBR, -1);
	error_control(&data, init_fork(&data), MALLOC, -1);
	error_control(&data, init_philo(&data), MALLOC, -1);
	error_control(&data, thread_create(&data), NULL, -1);
	if (data.p_count != data.arguments[0] - 1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

static int	arg_control(t_data *data, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][0] == '0')
			argv[i]++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FAILURE);
			j++;
		}
		while (argv[i][0])
		{
			data->arguments[i] = data->arguments[i] * 10 + (argv[i][0] - '0');
			argv[i]++;
		}
		if (data->arguments[i] > 2147483647)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->arguments[0]);
	if (!data->philo)
		return (FAILURE);
	memset(data->philo, 0, sizeof(t_philo) * data->arguments[0]);
	while (i < data->arguments[0])
	{
		memset(&data->philo[i], 0, sizeof(t_philo));
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].eat_last = get_time();
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1) % data->arguments[0]];
		i++;
	}
	return (SUCCESS);
}

static int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->arguments[0]);
	if (!data->fork)
		return (FAILURE);
	memset(data->fork, 0, sizeof(pthread_mutex_t) * data->arguments[0]);
	while (i < data->arguments[0])
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (FAILURE);
		i++;
	}
	if (pthread_mutex_init(&data->m_eat, NULL))
		return (data->m_error = 0, FAILURE);
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (data->m_error = 1, FAILURE);
	if (pthread_mutex_init(&data->m_print, NULL))
		return (data->m_error = 2, FAILURE);
	if (pthread_mutex_init(&data->m_ready, NULL))
		return (data->m_error = 3, FAILURE);
	return (data->m_error = 4, SUCCESS);
}

int	error_control(t_data *data, int error, char *message, int index)
{
	if (error == FAILURE)
	{
		if (data->m_error > 0)
			pthread_mutex_destroy(&data->m_eat);
		if (data->m_error > 1)
			pthread_mutex_destroy(&data->m_dead);
		if (data->m_error > 2)
			pthread_mutex_destroy(&data->m_print);
		if (data->m_error > 3)
			pthread_mutex_destroy(&data->m_ready);
		while (++index < data->arguments[0])
			if (data->fork)
				pthread_mutex_destroy(&data->fork[index]);
		if (data->philo)
			free(data->philo);
		if (data->fork)
			free(data->fork);
		if (message)
		{
			printf(RED "Error: %s\n" END, message);
			exit(EXIT_FAILURE);
		}
	}
	return (SUCCESS);
}
