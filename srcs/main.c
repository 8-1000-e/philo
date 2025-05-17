/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:39:16 by edubois-          #+#    #+#             */
/*   Updated: 2025/04/01 16:54:55 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	eat_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo && data->philo[i].has_eat >= data->nb_must_eat)
		i++;
	return (i == data->nb_philo);
}

void	*solo_philo(t_data *data, t_philo *philo)
{
	printf("[%lld] Philo %d has taken right fork\n",
		current_time() - data->start_t, philo->position);
	usleep(data->t_to_die * 1000);
	printf("[%lld] Philo 1 died\n", current_time() - data->start_t);
	return (NULL);
}

void	*routine(void *arg)
{
	static int	i;
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->m_philo_mutex);
	philo = &data->philo[i++];
	pthread_mutex_unlock(&data->m_philo_mutex);
	if (philo->position % 2 == 0)
		usleep(data->t_to_eat * 1000);
	while (!check_stop(data))
	{
		if (data->nb_philo == 1)
			return (solo_philo(data, philo));
		start_philo(data, philo);
		if (data->nb_must_eat != -1 && eat_enough(data))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};
	int				i;
	int				get_error;

	if (argc == 5 || argc == 6)
	{
		get_error = init_data(&data, argc, argv);
		if (!get_error)
			return (printf("Parameters error !\n"));
		if (get_error == 2)
			return (printf("Failed malloc !\n"));
		init_mutex(&data);
		i = -1;
		while (++i != data.nb_philo)
			pthread_create(&data.philo[i].thread, NULL, routine, &data);
		i = -1;
		while (++i != data.nb_philo)
			pthread_join(data.philo[i].thread, NULL);
		destroy_mutex(&data);
		free(data.philo);
		return (0);
	}
	return (printf("Parameters error !\n"));
}
