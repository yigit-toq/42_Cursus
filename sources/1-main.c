/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:08:22 by ytop              #+#    #+#             */
/*   Updated: 2024/07/04 19:17:54 by ytop             ###   ########.fr       */
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
		error_control(&data, FAILURE, "Wrong number of arguments");
	else if (argc == 6 && argv[5][0] == '0')
		return (EXIT_FAILURE);
	data.s_time = get_time();
	error_control(&data, arg_control(&data, argv + 1), "Argument is not valid");
	error_control(&data, init_fork(&data), MALLOC);
	error_control(&data, init_philo(&data), MALLOC);
	printf("%s | %s | %s\n-------------------\n", "TIME", "ID", "MESSAGE");
	error_control(&data, thread_create(&data), NULL);
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
		if (j > 10 || (j == 10 && argv[i][j - 1] - '0' > 7))
			return (FAILURE);
		while (argv[i][0])
		{
			data->arguments[i] = data->arguments[i] * 10 + (argv[i][0] - '0');
			argv[i]++;
		}
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
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
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
		return (FAILURE);
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&data->m_print, NULL))
		return (FAILURE);
	return (SUCCESS);
}

int	error_control(t_data *data, int error, char *message)
{
	int	i;

	i = -1;
	if (error == FAILURE)
	{
		pthread_mutex_destroy(&data->m_eat);
		pthread_mutex_destroy(&data->m_dead);
		pthread_mutex_destroy(&data->m_print);
		while (++i < data->arguments[0])
			if (data->fork)
				pthread_mutex_destroy(&data->fork[i]);
		if (data->philo)
			free(data->philo);
		if (data->fork)
			free(data->fork);
		if (message)
		{
			printf(RED);
			printf("Error: %s\n", message);
			printf(END);
			exit(EXIT_FAILURE);
		}
	}
	return (SUCCESS);
}
