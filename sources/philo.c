/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:08:22 by ytop              #+#    #+#             */
/*   Updated: 2024/07/02 19:48:42 by ytop             ###   ########.fr       */
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
	t_philo	*philo;
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		ft_exit(&data, FAILURE, "Wrong number of arguments");
	else if (argc == 6 && argv[5][0] == '0')
		return (EXIT_FAILURE);
	ft_exit(&data, arg_control(&data, argv + 1), "Argument not number.");
	ft_exit(&data, init_fork(&data), "Malloc not allocated.");
	ft_exit(&data, init_philo(&data), "Malloc not allocated.");
	data.s_time = get_time();
	data.s_dead = 0;
	philo = data.philo;
	i = -1;
	while (++i < data.arguments[0])
		if (pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]))
			ft_exit(&data, FAILURE, "Thread not created.");
	i = -1;
	while (++i < data.arguments[0])
		if (pthread_join(philo[i].thread, NULL))
			ft_exit(&data, FAILURE, "Thread not joined.");
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
		data->philo[i].left_fork = data->fork[i];
		data->philo[i].right_fork = data->fork[(i + 1) % data->arguments[0]];
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
	if (pthread_mutex_init(&data->print, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&data->dead, NULL))
		return (FAILURE);
	return (SUCCESS);
}

void	ft_exit(t_data *data, int error, char *message)
{
	int	i;

	i = 0;
	if (error == FAILURE)
	{
		pthread_mutex_destroy(&data->print);
		while (i < data->arguments[0])
		{
			if (data->fork)
				if (pthread_mutex_destroy(&data->fork[i]))
					ft_exit(data, FAILURE, "Mutex not destroyed.");
			i++;
		}
		if (data->philo)
			free(data->philo);
		if (data->fork)
			free(data->fork);
		printf(RED);
		printf("Error: %s\n", message);
		printf(END);
		exit(EXIT_FAILURE);
	}
	return ;
}
