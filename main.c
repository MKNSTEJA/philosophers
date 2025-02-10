/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:37:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/10 12:58:18 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_philo *philos, t_data *data);

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			ret;
    
    parse_info(&data, argv, argc);
	if (init_data(&data) != 0)
		return (1);
	if (init_philos(&philos, &data) != 0)
	{
		free(data.forks);
		return (1);
	}
	ret = pthread_create(&monitor_thread, NULL, routine, (void *)philos);
	if (ret != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		cleanup(philos, &data);
		return (1);
	}
	ret = start_philos(&philos, &data);
	pthread_join(monitor_thread, NULL);
	cleanup(philos, &data);
	return (0);
}

void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	data->forks = NULL;
	free(philos);
	philos = NULL;
}
