/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:56:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/04/02 11:44:04 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(t_philo *philo);
void	left_fork_first(t_philo *philo);
void	right_fork_first(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num == 1)
		return (one_philo(philo));
	else if (philo->id % 2 == 0 || philo->id == philo->data->num)
	{
		print_task(philo->data, philo->id, "is thinking");
		rest(philo->data->time_to_eat, philo);
		usleep(100);
	}
	while (1 && philo->data->num > 1)
	{
		usleep(300);
		if (rip_checker(philo->data) != 0)
			break ;
		if (philo->id < philo->data->num && !rip_checker(philo->data))
			left_fork_first(philo);
		else if (philo->id == philo->data->num && !rip_checker(philo->data))
			right_fork_first(philo);
		print_task(philo->data, philo->id, "is sleeping");
		rest(philo->data->time_to_sleep, philo);
		print_task(philo->data, philo->id, "is thinking");
	}
	return ((void *)0);
}

void	*one_philo(t_philo *philo)
{
	print_task(philo->data, philo->id, "is thinking");
	rest(philo->data->time_to_die, philo);
	usleep(1000);
	return (NULL);
}

void	left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_task(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_task(philo->data, philo->id, "has taken a fork");
	print_task(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->lock_last_meal_time);
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->lock_last_meal_time);
	rest(philo->data->time_to_eat, philo);
	increment_meal_count(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_task(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_task(philo->data, philo->id, "has taken a fork");
	print_task(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->lock_last_meal_time);
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->lock_last_meal_time);
	rest(philo->data->time_to_eat, philo);
	increment_meal_count(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}
