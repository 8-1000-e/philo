/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:39:16 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/21 16:05:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	display_data(t_data data)
{
	printf("nb_philo    %d\n",data.nb_philo);
	printf("t_to_die    %d\n",data.t_to_die);
	printf("t_to_eat    %d\n",data.t_to_eat);
	printf("t_to_sleep  %d\n",data.t_to_sleep);
	printf("nb_must_eat %d\n",data.nb_must_eat);
	printf("has_eat     %d\n",data.has_eat);
}

static	int	init_data(t_data *data, int argc, char **argv)
{
	int	error;

	error = 0;
	data->nb_philo = ft_putnbr(*++argv, &error);
	if (error || !data->nb_philo)
		return (0);
	data->t_to_die = ft_putnbr(*++argv, &error);
	if (error || !data->t_to_die)
		return (0);
	data->t_to_eat = ft_putnbr(*++argv, &error);
	if (error || !data->t_to_eat)
		return (0);
	data->t_to_sleep = ft_putnbr(*++argv, &error);
	if (error || !data->t_to_sleep)
		return (0);
	if (argc == 6)
	{
		data->nb_must_eat = ft_putnbr(*++argv, &error);
		if (error)
			return (0);
	}
	data->philo = ft_calloc(data->nb_philo, sizeof(t_philo));
	if (!data->philo)
		exit(2);
	return (1);
}

int	stop(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->stop_mutex);
	result = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (result);
}

void	routine(void *arg)
{
    t_data  *data;
	t_philo	*philo;

	philo = (t_philo*)arg;
	data = philo->data;
	while (!stop(data))
	{
		
	}
}

int main(int argc, char **argv)
{
    static t_data  data = {0};
	int	i;

    if (argc == 5 || argc == 6)
    {
		if (!init_data(&data, argc, argv))
			return (printf("Parameters error !\n"));
		init_mutex(&data);
		i = -1;
		while (++i != data.nb_philo)
			pthread_create(data.philo[i].thread, NULL, routine, &data.philo[i]);
		i = -1;
		while (++i != data.nb_philo)
			pthread_join(data.philo[i].thread, NULL);
		destroy_mutex(&data);
	}
	return (printf("Parameters error !\n"));
}
