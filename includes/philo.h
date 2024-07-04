/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:54 by ytop              #+#    #+#             */
/*   Updated: 2024/07/04 20:45:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define PURPLE	"\033[0;35m"
# define BLUE	"\033[0;34m"
# define YELLOW	"\033[0;33m"
# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define END	"\033[0m"

# define SUCCESS	1
# define FAILURE	0

# define GET		1
# define SET		0

# define TRUE		1
# define FALSE		0

# define MALLOC "Malloc not allocated"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	int				id;
	int				eat_count;
	long long		eat_last;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_print;
	t_philo			*philo;
	long long		s_time;
	int				s_dead;
	int				arguments[5];
}					t_data;

void				routine(t_philo *philo);

int					thread_create(t_data *data);

int					death_control(t_philo *philo);

int					error_control(t_data *data, int error, char *message);

int					set_int(pthread_mutex_t *mutex, int *dest, int value);

int					get_int(pthread_mutex_t *mutex, int *dest);

long long			get_time(void);

int					ft_sleep(int time);
#endif
