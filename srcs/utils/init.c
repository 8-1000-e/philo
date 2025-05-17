/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:34:32 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 16:55:28 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

int	init_all_data(t_data *data, int argc, char **argv, int error)
{
	data->start_t = current_time();
	if (argc == 6)
	{
		data->nb_must_eat = ft_secur_atol(*++argv, &error);
		if (error)
			return (0);
	}
	else
		data->nb_must_eat = -1;
	data->philo = malloc((data->nb_philo + 1) * sizeof(t_philo));
	if (!data->philo)
		return (2);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	error;

	error = 0;
	data->stop = 0;
	data->nb_philo = ft_secur_atol(*++argv, &error);
	if (error || !data->nb_philo)
		return (0);
	data->t_to_die = ft_secur_atol(*++argv, &error);
	if (error || !data->t_to_die)
		return (0);
	data->t_to_eat = ft_secur_atol(*++argv, &error);
	if (error || !data->t_to_eat)
		return (0);
	data->t_to_sleep = ft_secur_atol(*++argv, &error);
	if (error || !data->t_to_sleep)
		return (0);
	return (init_all_data(data, argc, argv, error));
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->m_philo_mutex, NULL);
	pthread_mutex_init(&data->p_mutex, NULL);
	while (i < data->nb_philo)
	{
		data->philo[i].has_eat = 0;
		data->philo[i].position = i + 1;
		pthread_mutex_init(&data->philo[i].r_fork_mutex, NULL);
		data->philo[i].last_eat = current_time();
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].l_fork_mutex = data->philo[(i + 1)
			% data->nb_philo].r_fork_mutex;
		i++;
	}
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->p_mutex);
	pthread_mutex_destroy(&data->m_philo_mutex);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].l_fork_mutex);
		if (data->nb_philo > 1)
			pthread_mutex_destroy(&data->philo[i].r_fork_mutex);
		i++;
	}
}
