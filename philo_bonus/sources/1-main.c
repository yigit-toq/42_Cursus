/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:08:22 by ytop              #+#    #+#             */
/*   Updated: 2024/07/15 17:52:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	arg_control(t_data *data, char **argv);
static int	init_philo(t_data *data);
static int	init_sem(t_data *data);

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
	error_control(&data, init_sem(&data), MALLOC, -1);
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
	data->philo->pid = malloc(sizeof(int) * data->arguments[0]);
	if (!data->philo)
		return (FAILURE);
	memset(data->philo->pid, 0, sizeof(int) * data->arguments[0]);
	while (i < data->arguments[0])
	{
		memset(&data->philo[i], 0, sizeof(int));
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].eat_last = get_time();
		i++;
	}
	return (SUCCESS);
}

static int	init_sem(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	sem_unlink("sem_death");
	philo->s_fork = sem_open("sem_fork", O_CREAT, 0644, data->arguments[0]);
	if (philo->s_fork == SEM_FAILED)
		return (FAILURE);
	philo->s_print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (philo->s_print == SEM_FAILED)
		return (FAILURE);
	philo->s_death = sem_open("sem_death", O_CREAT, 0644, 1);
	if (philo->s_death == SEM_FAILED)
		return (FAILURE);
	return (SUCCESS);
}

int	error_control(t_data *data, int error, char *message, int index)
{
	(void)index;
	if (error == FAILURE)
	{
		sem_close(data->philo->s_fork);
		sem_close(data->philo->s_death);
		sem_unlink("sem_fork");
		sem_unlink("sem_print");
		sem_unlink("sem_death");
		free(data->philo->pid);
		if (message)
		{
			printf(RED "Error: %s\n" END, message);
			exit(EXIT_FAILURE);
		}
	}
	return (SUCCESS);
}
