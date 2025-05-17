/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:59:59 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 16:54:34 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	check_stop(t_data *data)
{
	int	value;

	value = 0;
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
		value = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (value);
}

void	start_philo(t_data *data, t_philo *philo)
{
	make_stop(data, philo->position);
	p_take_fork(data, philo);
	p_eat(data, philo);
	make_stop(data, philo->position);
	p_sleep(data, philo);
	make_stop(data, philo->position);
	p_think(data, philo);
}
