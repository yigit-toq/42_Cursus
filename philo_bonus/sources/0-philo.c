/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:46:39 by ytop              #+#    #+#             */
/*   Updated: 2024/07/15 17:51:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	loop(t_philo *philo, t_data *data);
static int	print_message(t_philo *philo, char *mesagge, char *color);

void	routine(t_philo *philo)
{
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
	while (!philo->data->s_dead)
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
	sem_wait(philo->s_fork);
	print_message(philo, FORK, YELLOW);
	sem_wait(philo->s_fork);
	print_message(philo, FORK, YELLOW);
	sem_post(philo->s_fork);
	print_message(philo, EAT, GREEN);
	philo->eat_last = get_time();
	philo->eat_count++;
	sem_post(philo->s_fork);
	ft_sleep(data->arguments[2]);
	sem_post(philo->s_fork);
	sem_post(philo->s_fork);
	print_message(philo, SLEEP, BLUE);
	ft_sleep(data->arguments[3]);
	print_message(philo, THINK, PURPLE);
	return (SUCCESS);
}

static int	print_message(t_philo *philo, char *mesagge, char *color)
{
	t_data	*data;

	data = philo->data;
	sem_wait(philo->s_print);
	if ((philo->eat_count == data->arguments[4] && data->arguments[4])
		|| data->s_dead)
		return (FAILURE);
	printf("%s", color);
	printf("%-6lld %d %s\n", get_time() - data->s_time, philo->id, mesagge);
	printf("%s", END);
	sem_post(philo->s_print);
	return (SUCCESS);
}

int	thread_create(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	while (i < data->arguments[0])
	{
		*philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			routine(&philo[i]);
			exit(0);
		}
		data->p_count = i++;
	}
	death_control(data);
	i = 0;
	while (i < data->arguments[0])
	{
		waitpid(-1, NULL, 0);
		ft_kill(data);
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
		sem_wait(philo[i].s_death);
		if (get_time() - philo[i].eat_last >= data->arguments[1])
		{
			if (philo[i].eat_count == data->arguments[4] && data->arguments[4])
				return (FAILURE);
			print_message(&philo[i], DEAD, RED);
			data->s_dead = 1;
			sem_post(philo[i].s_death);
			return (FAILURE);
		}
		if (i == data->arguments[0] - 1)
			i = 0;
		i++;
	}
	return (SUCCESS);
}
