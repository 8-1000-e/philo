/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:25 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 17:00:39 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	p_take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (!check_stop(data))
	{
		pthread_mutex_lock(&data->p_mutex);
		printf("[%lld] Philo %d has taken left fork\n",
			current_time() - data->start_t, philo->position);
		pthread_mutex_unlock(&data->p_mutex);
	}
	pthread_mutex_lock(&philo->r_fork_mutex);
	if (!check_stop(data))
	{
		pthread_mutex_lock(&data->p_mutex);
		printf("[%lld] Philo %d has taken right fork\n",
			current_time() - data->start_t, philo->position);
		pthread_mutex_unlock(&data->p_mutex);
	}
}

void	p_eat(t_data *data, t_philo *philo)
{
	if (!check_stop(data))
	{
		pthread_mutex_lock(&data->p_mutex);
		printf("[%lld] Philo %d is eating\n",
			current_time() - data->start_t, philo->position);
		pthread_mutex_unlock(&data->p_mutex);
	}
	custom_sleep(data, philo, data->t_to_eat);
	make_stop(data, philo->position);
	pthread_mutex_unlock(&philo->l_fork_mutex);
	pthread_mutex_unlock(&philo->r_fork_mutex);
	make_stop(data, philo->position);
	philo->has_eat++;
	philo->last_eat = current_time();
}

void	p_sleep(t_data *data, t_philo *philo)
{
	if (!check_stop(data))
	{
		pthread_mutex_lock(&data->p_mutex);
		printf("[%lld] Philo %d is sleeping\n",
			current_time() - data->start_t, philo->position);
		pthread_mutex_unlock(&data->p_mutex);
	}
	custom_sleep(data, philo, data->t_to_sleep);
	make_stop(data, philo->position);
}

void	p_think(t_data *data, t_philo *philo)
{
	if (!check_stop(data))
	{
		pthread_mutex_lock(&data->p_mutex);
		printf("[%lld] Philo %d is thinking\n",
			current_time() - data->start_t, philo->position);
		pthread_mutex_unlock(&data->p_mutex);
	}
}
