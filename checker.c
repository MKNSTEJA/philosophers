/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:02 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 20:12:58 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int		wasted(t_philo *philos, t_data *data, long timestamp, int i);

int		check_philosophers(t_philo *philos);

void	*fbi(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!rip_checker(data))
	{
		if (check_philosophers(philos) == -1)
			break ;
		usleep(100);
	}
	// printf("stuck in fbi?\n");
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
		if (wasted(&philos[i], philos[i].data, timestamp, i) == -1)
			return (-1);
    pthread_mutex_lock(&philos[i].lock_meal_count);
		if (data->must_eat != -1 && philos[i].meal_count < data->must_eat)
			max_meals_done = 0;
    pthread_mutex_unlock(&philos[i].lock_meal_count);
		i++;
	}
	if (data->must_eat != -1 && max_meals_done == 1)
	{
		pthread_mutex_lock(&data->lock_stop);
		data->stop = 1;
		pthread_mutex_unlock(&data->lock_stop);
	}
	return (0);
}

int	wasted(t_philo *philos, t_data *data, long timestamp, int i)
{
	(void)i;
	pthread_mutex_lock(&philos->lock_last_meal_time);
	pthread_mutex_lock(&data->print_mutex);
	if (timestamp - philos->last_meal_time > data->time_to_die)
	{
		// printf("%ld - %ld > %d\n", timestamp, philos->last_meal_time,
			// data->time_to_die);
		printf("%ld %d died\n", timestamp - data->start_time, philos->id);
		pthread_mutex_lock(&data->lock_stop);
		data->stop = 1;
		pthread_mutex_unlock(&data->lock_stop);
		pthread_mutex_unlock(&philos->lock_last_meal_time);
		pthread_mutex_unlock(&data->print_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&philos->lock_last_meal_time);
	return (0);
}
