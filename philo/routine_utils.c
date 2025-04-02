/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:58:13 by kmummadi          #+#    #+#             */
/*   Updated: 2025/04/02 14:43:22 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	rip_checker(t_data *data)
{
	int	val;

	val = 0;
	pthread_mutex_lock(&data->lock_stop);
	if (data->stop != 0)
		val = 1;
	pthread_mutex_unlock(&data->lock_stop);
	return (val);
}

void	increment_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_meal_count);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock_meal_count);
	return ;
}

void	print_task(t_data *data, int id, char *action)
{
	if (rip_checker(data) != 0)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", get_timestamp() - data->start_time, id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	rest(int sleep_time, t_philo *philo)
{
	long	time_stamp;

	time_stamp = get_timestamp();
	while ((get_timestamp() - time_stamp < sleep_time)
		&& rip_checker(philo->data) == 0)
		usleep(500);
}
