/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:08:22 by ytop              #+#    #+#             */
/*   Updated: 2024/06/27 18:10:06 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	arg_control(t_data *data, char **argv);
static int	ft_atoi(const char *str);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		error_control(0, 0, "Wrong number of arguments");
	error_control(arg_control(&data, argv + 1), 0, "Argument is not a number");
	return (0);
}

static int	arg_control(t_data *data, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] == '0')
			argv[i]++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		if (j > 10 || (j == 10 && argv[i][j - 1] - '0' > 7))
			return (0);
		data->arguments[i] = ft_atoi(argv[i]);
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

void	error_control(int error, int flag, char *message)
{
	(void)flag;
	if (!error)
	{
		printf(RED);
		printf("Error: %s\n", message);
		printf(END);
		exit(1);
	}
	return ;
}
