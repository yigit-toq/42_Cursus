/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:54 by ytop              #+#    #+#             */
/*   Updated: 2024/07/01 18:03:22 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define RED "\033[0;31m"
# define END "\033[0m"

# define SUCCESS 1
# define FAILURE 0

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				eat_last;
	int				is_dead;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	int				s_time;
	int				arguments[5];
}				t_data;

void		eat(t_philo *philo);

void		ft_exit(t_data *data, int error, char *message);

int			print_message(t_philo *philo, char *mesagge);

int			get_time(void);

#endif
