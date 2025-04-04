/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:38:48 by kmummadi          #+#    #+#             */
/*   Updated: 2025/04/02 14:30:03 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->num));
	while (i < data->num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_forks(data, i));
		i++;
	}
	return (0);
}

int	init_philos(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	(*philo) = ft_calloc(data->num, sizeof(t_philo));
	if (!(*philo))
	{
		printf("Error with allocation for philo\n");
		return (-1);
	}
	(*philo)->data = data;
	while (i < (*philo)->data->num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].last_meal_time = data->start_time;
		(*philo)[i].left_fork = i;
		if (pthread_mutex_init(&(*philo)[i].lock_meal_count, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(&(*philo)[i].lock_last_meal_time, NULL) != 0)
			return (-1);
		(*philo)[i].right_fork = (i + 1) % (data->num);
		i++;
	}
	return (0);
}

int	destroy_forks(t_data *data, int i)
{
	printf("Error with init of Fork->%d\n", i);
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	return (-1);
}

int	init_data(t_data *data)
{
	data->start_time = get_timestamp();
	if (init_forks(data) < 0)
		return (-1);
	data->stop = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (destroy_forks(data, data->num));
	if (pthread_mutex_init(&data->lock_stop, NULL) != 0)
		return (destroy_forks(data, data->num));
	return (0);
}
