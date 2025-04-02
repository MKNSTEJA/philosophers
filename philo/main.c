/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:37:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/04/02 16:12:10 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	cleanup(t_philo *philos, t_data *data);
int		init_everything(t_data **data, t_philo **philos, char **argv, int argc);

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			ret;

	if (errors(argc, argv) != 0)
		return (-1);
	data = ft_calloc(1, sizeof(t_data));
	philos = NULL;
	if (!data)
		return (-1);
	init_everything(&data, &philos, argv, argc);
	ret = pthread_create(&monitor_thread, NULL, fbi, (void *)philos);
	if (ret != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		return (cleanup(philos, data), 1);
	}
	ret = start_philos(&philos, &data);
	pthread_join(monitor_thread, NULL);
	cleanup(philos, data);
	free(data);
	data = NULL;
	return (0);
}

void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].lock_meal_count);
		pthread_mutex_destroy(&philos[i].lock_last_meal_time);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->lock_stop);
	free(data->forks);
	data->forks = NULL;
	free(philos);
	philos = NULL;
}

int	init_everything(t_data **data, t_philo **philos, char **argv, int argc)
{
	parse_info(*data, argv, argc);
	if (init_data(*data) != 0)
		return (-1);
	if (init_philos(philos, *data) != 0)
		return (free((*data)->forks), -1);
	return (0);
}
