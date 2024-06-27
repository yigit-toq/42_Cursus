/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:54 by ytop              #+#    #+#             */
/*   Updated: 2024/06/27 18:01:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define RED "\033[0;31m"
# define END "\033[0m"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				eat_last;
}				t_philo;

typedef struct s_data
{
	t_philo	*philo;
	int		arguments[5];
}				t_data;

void	error_control(int function, int flag, char *message);

#endif
