/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:11:02 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/07 12:07:02 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "./ft_printf/ft_printf.h"

typedef enum e_task
{
    EAT,
    SLEEP,
    THINK,
    DIE,
} t_task;

typedef struct s_data
{
    int num;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    long start_time;
    int must_eat;
    int meal_count;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    int stop;
    int dead;
} t_data;

typedef struct s_philo
{
    int id;
    pthread_t thread;
    int left_fork;
    int right_fork;
    int last_meal_time;
    int meal_count;
    t_data *data;
} t_philo;

int	ft_atoi(char *str);
long	get_timestamp(void);
int	init_forks(t_data *data);
int	init_philo(t_philo **philo, t_data *data);
int	destroy_forks(t_data *data, int i);
int stop_philos(t_philo **philo, int i);
void *routine(void *arg);

#endif