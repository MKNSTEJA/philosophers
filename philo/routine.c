/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:56:29 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 20:15:08 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_task(t_data *data, int id, char *action);
void	rest(int sleep_time, t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if(philo->data->num == 1)
	{
		print_task(philo->data, philo->id, "is thinking");
		rest(philo->data->time_to_die, philo);
		usleep(1000);
    return (NULL);
	}
	else if(philo->id % 2 == 0 || philo->id == philo->data->num)
	{
		print_task(philo->data, philo->id, "is thinking");
		rest(philo->data->time_to_eat, philo);
    usleep(100);
	}
	while (1 && philo->data->num > 1)
	{
		if(rip_checker(philo->data) != 0)
			break;
		// int rip = rip_checker(philo->data);
		// printf("rip: %d, id: %d, stop: %d\n", rip, philo->id, philo->data->stop);
		// if(rip != 0)
		// 	break;
		if (philo->id < philo->data->num && !rip_checker(philo->data))
		{
			// printf("philo%d trying to lock left fork\n", philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			// printf("philo%d trying to lock right fork\n", philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			print_task(philo->data, philo->id, "is eating");
			pthread_mutex_lock(&philo->lock_last_meal_time);
			philo->last_meal_time = get_timestamp();
			pthread_mutex_unlock(&philo->lock_last_meal_time);
			rest(philo->data->time_to_eat, philo);
			increment_meal_count(philo);
			// printf("philo%d trying to unlock right fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			// printf("philo%d trying to unlock left fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			// printf("philo%d done unlocking forks\n", philo->id);
		}
		else if(philo->id == philo->data->num && !rip_checker(philo->data))
		{
			// printf("philo%d trying to lock right fork\n", philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			// printf("philo%d trying to lock left fork\n", philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			print_task(philo->data, philo->id, "has taken a fork");
			print_task(philo->data, philo->id, "is eating");
			pthread_mutex_lock(&philo->lock_last_meal_time);
			philo->last_meal_time = get_timestamp();			
			pthread_mutex_unlock(&philo->lock_last_meal_time);
			rest(philo->data->time_to_eat, philo);
			increment_meal_count(philo);
			// printf("philo%d trying to unlock left fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			// printf("philo%d trying to unlock right fork\n", philo->id);
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			// printf("philo%d done unlocking forks\n", philo->id);

		}
		print_task(philo->data, philo->id, "is sleeping");
		rest(philo->data->time_to_sleep, philo);
		print_task(philo->data, philo->id, "is thinking");
    	// printf("id: %d stop: %d\n", philo->id, philo->data->stop);
	}
	// printf("stuck in routine? \n");
	return ((void *)0);
}

void	print_task(t_data *data, int id, char *action)
{
	if(rip_checker(data) != 0)
		return;
	// printf("philo trying to print that \"%s\"\n", action);
	pthread_mutex_lock(&data->print_mutex);
	// printf("philo%d locked print\n", id);
	printf("%ld %d %s\n", get_timestamp() - data->start_time, id, action);
	// printf("unlocking print\n");
	pthread_mutex_unlock(&data->print_mutex);
	// printf("philo%d done unlocking print\n", id);
}

void	rest(int sleep_time, t_philo *philo)
{
	long	time_stamp;

	time_stamp = get_timestamp();
	while ((get_timestamp() - time_stamp < sleep_time) && rip_checker(philo->data) == 0)
		usleep(300);
}
