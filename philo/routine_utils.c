/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:58:13 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 15:26:46 by kmummadi         ###   ########.fr       */
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
