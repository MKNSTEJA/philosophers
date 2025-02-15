/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknsteja <mknsteja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:56:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 12:11:21 by mknsteja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_task(t_data *data, int id, char *action);
void	rest(int sleep_time);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if(philo->id % 2 == 0 || philo->id == philo->data->num)
  {
		print_task(philo->data, philo->id, "is thinking");
    rest(philo->data->time_to_eat);
  }
	while (philo->data->stop == 0)
	{
		// usleep(100);
		if (philo->id < philo->data->num)
		{
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
		}
		else if(philo->id == philo->data->num)
		{
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
		}
		print_task(philo->data, philo->id, "is eating");
		philo->last_meal_time = get_timestamp();
		rest(philo->data->time_to_eat);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		print_task(philo->data, philo->id, "is sleeping");
		rest(philo->data->time_to_sleep);
		print_task(philo->data, philo->id, "is thinking");
	}
	return ((void *)0);
}

void	print_task(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", get_timestamp() - data->start_time, id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	rest(int sleep_time)
{
	long	time_stamp;

	time_stamp = get_timestamp();
	while (get_timestamp() - time_stamp < sleep_time)
		usleep(300);
}
