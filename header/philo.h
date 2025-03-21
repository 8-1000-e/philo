/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:37:40 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/21 16:05:42 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data
{
	int nb_philo;
	t_philo	*philo;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_sleep;
	int	nb_must_eat;
	int	has_eat;
	pthread_mutex_t	stop_mutex;
	int	stop;
}	t_data;

typedef struct s_philo
{
	int	last_eat;
	int	last_sleep;
	t_data	*data;
	pthread_t thread;
}	t_philo;

int	init_mutex(t_data *data);
int	destroy_mutex(t_data *data);
int	main(int argc, char **argv);
int ft_secur_atoi(char *str, int *error);

#endif