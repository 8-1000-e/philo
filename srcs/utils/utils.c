/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:49:12 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/21 16:05:28 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

int	ft_isdigit(int number)
{
	return (number >= '0' && number <= '9');
}

int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->stop_mutex, NULL);
}

int	destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->stop_mutex);
}

int ft_secur_atoi(char *str, int *error)
{
    unsigned int	nb;

    nb = 0;
	if (!str)
		return (nb);
    if (*str == '-')
        *error = 1;
    if (*str == '+')
		str++;
	while (*str)
	{
		if (nb > INT_MAX || !ft_isdigit(*str))
		{
			*error = 1;
			return (0);
		}		
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}
