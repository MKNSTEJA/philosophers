/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:02 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/11 13:35:52 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosophers(t_philo *philos);

void	*fbi(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (data->stop == 0)
	{
		if (check_philosophers(philos) == -1)
			break ;
		usleep(100);
	}
	return ((void *)0);
}

int	check_philosophers(t_philo *philos)
{
	t_data	*data;
	int		i;
	int		max_meals_done;
	long	timestamp;

	data = philos[0].data;
	i = 0;
	max_meals_done = 1;
	while (i < data->num)
	{
		timestamp = get_timestamp();
		pthread_mutex_lock(&data->print_mutex);
		if (timestamp - philos[i].last_meal_time > data->time_to_die)
		{
			printf("%ld - %ld > %d\n", timestamp, philos[i].last_meal_time, data->time_to_die);
			printf("%ld %d died\n", timestamp - data->start_time, philos[i].id);
			data->stop = 1;
			return (-1);
		}
		pthread_mutex_unlock(&data->print_mutex);
		if (data->must_eat != -1 && philos[i].meal_count < data->must_eat)
			max_meals_done = 0;
		i++;
	}
	if (data->must_eat != -1 && max_meals_done == data->num)
		data->stop = 1;
	return (0);
}
