/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:54 by ytop              #+#    #+#             */
/*   Updated: 2024/07/03 15:18:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define RED "\033[0;31m"
# define END "\033[0m"

# define SUCCESS	1
# define FAILURE	0

# define GET		1
# define SET		0

# define MALLOC		"Malloc not allocated."

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	int				id;
	int				eat_last;
	int				eat_count;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	int				s_time;
	int				s_dead;
	int				arguments[5];
}				t_data;

void	routine(t_philo *philo);

void	ft_usleep(long long time);

void	ft_exit(t_data *data, int error, char *message);

void	set_get_int(pthread_mutex_t *mutex, int *dest, int value, int type);

int		print_message(t_philo *philo, char *mesagge);

int		get_time(void);

#endif
