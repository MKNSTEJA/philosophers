/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 07:11:09 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/07 07:31:08 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philos(t_philo **philo, t_data *data)
{
	int	i;

	if (init_forks(data) < 0)
		return (printf("Error with init_forks\n"), -1);
	i = 0;
	while (i < data->num)
	{
		if (!pthread_create(&(*philo)[i].thread, NULL, routine,
				(void *)&(*philo)[i]))
			return (stop_philos(philo, i));
		i++;
	}
	i = 0;
	while (i < data->num)
	{
		pthread_join(&(*philo)[i].thread, NULL);
		i++;
	}
	return (0);
}

int	stop_philos(t_philo **philo, int i)
{
	printf("Error with creating thread for philo->%d", i);
	while ((--i) >= 0)
		pthread_join((*philo)[i].thread, NULL);
	return (-1);
}
