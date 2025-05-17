/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:49:12 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 16:55:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

void	make_stop(t_data *data, int i)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (current_time() - data->philo[i - 1].last_eat > data->t_to_die)
	{
		if (!data->stop)
		{
			pthread_mutex_lock(&data->p_mutex);
			printf("[%lld] Philo %d died\n",
				current_time() - data->start_t, i);
			pthread_mutex_unlock(&data->p_mutex);
		}
		data->stop = 1;
	}
	pthread_mutex_unlock(&data->stop_mutex);
}

void	custom_sleep(t_data *data, t_philo *philo, int time)
{
	while (time > 12 && !check_stop(data))
	{
		make_stop(data, philo->position);
		usleep(12 * 1000);
		time -= 12;
	}
	make_stop(data, philo->position);
	usleep(time * 1000);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_isdigit(int number)
{
	return (number >= '0' && number <= '9');
}

long long	ft_secur_atol(char *str, int *error)
{
	long long	nb;

	nb = 0;
	if (!str)
		return (nb);
	if (*str == '-')
		*error = 1;
	while (*str == '+')
		str++;
	while (*str)
	{
		if (nb > (LLONG_MAX - (*str - '0')) / 10 || !ft_isdigit(*str))
		{
			*error = 1;
			return (0);
		}
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}
