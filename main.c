/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknsteja <mknsteja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:37:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 12:29:11 by mknsteja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_philo *philos, t_data *data);

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			ret;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (-1);
	parse_info(data, argv, argc);
	if (init_data(data) != 0)
		return (1);
	if (init_philos(&philos, data) != 0)
	{
		free(data->forks);
		return (1);
	}
	ret = pthread_create(&monitor_thread, NULL, fbi, (void *)philos);
	if (ret != 0)
	{
		printf("Error: Failed to create monitor thread.\n");
		cleanup(philos, data);
		return (1);
	}
	ret = start_philos(&philos, &data);
	printf("passes 1\n");
	pthread_join(monitor_thread, NULL);
	printf("passes 2\n");
	cleanup(philos, data);
	printf("passes 3\n");
	return (0);
}

void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		printf("stuck in cleanup\n");
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	data->forks = NULL;
	free(philos);
	philos = NULL;
}
