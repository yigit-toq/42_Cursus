/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:54 by ytop              #+#    #+#             */
/*   Updated: 2024/07/15 17:51:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <pthread.h>

# define PURPLE		"\033[0;35m"
# define BLUE		"\033[0;34m"

# define YELLOW		"\033[0;33m"
# define GREEN		"\033[0;32m"
# define RED		"\033[0;31m"

# define END		"\033[0m"

# define SUCCESS	1
# define FAILURE	0

# define GET		1
# define SET		0

# define TRUE		1
# define FALSE		0

# define MALLOC 	"Malloc not allocated."
# define NOTNBR		"Argument is not valid."
# define NOTAGR		"Wrong number of arguments."

# define FORK		"has taken a fork"

# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define EAT		"is eating"

# define DEAD		"died"

typedef struct s_philo
{
	struct s_data	*data;
	sem_t			*s_fork;
	sem_t			*s_death;
	sem_t			*s_print;
	pid_t			*pid;
	int				id;
	int				eat_count;
	long long		eat_last;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	long long		arguments[5];
	long long		s_time;
	int				s_dead;
	int				p_count;
	int				m_error;
}					t_data;

void		ft_kill(t_data *data);

void		routine(t_philo *philo);

int			thread_create(t_data *data);

int			death_control(t_data *data);

int			error_control(t_data *data, int error, char *message, int index);

int			set_int(pthread_mutex_t *mutex, int *dest, int value);

int			get_int(pthread_mutex_t *mutex, int *dest);

int			ft_sleep(int time);

long long	get_time(void);
#endif
