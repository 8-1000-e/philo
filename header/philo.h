/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:37:40 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 16:54:19 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long long		start_t;
	int				nb_philo;
	t_philo			*philo;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				nb_must_eat;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	p_mutex;
	pthread_mutex_t	m_philo_mutex;
	int				stop;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	r_fork_mutex;
	long long		last_eat;
	long long		last_sleep;
	int				has_eat;
	int				position;
	pthread_t		thread;
}	t_philo;

void		init_mutex(t_data *data);
void		destroy_mutex(t_data *data);
int			main(int argc, char **argv);
long long	ft_secur_atol(char *str, int *error);
void		start_philo(t_data *data, t_philo *philo);
int			init_all_data(t_data *data, int argc, char **argv, int error);
int			init_data(t_data *data, int argc, char **argv);
void		custom_sleep(t_data *data, t_philo *philo, int time);
long long	current_time(void);
void		make_stop(t_data *data, int i);
void		p_take_fork(t_data *data, t_philo *philo);
void		p_eat(t_data *data, t_philo *philo);
void		p_sleep(t_data *data, t_philo *philo);
void		p_think(t_data *data, t_philo *philo);
int			check_stop(t_data *data);

#endif