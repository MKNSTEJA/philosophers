/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:11:02 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/15 21:00:26 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_task
{
	EAT,
	SLEEP,
	THINK,
	DIE,
}					t_task;

typedef struct s_data
{
	int				num;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long			start_time;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	lock_stop;
	int				stop;
	int				dead;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	lock_meal_count;
	long			last_meal_time;
	pthread_mutex_t lock_last_meal_time;
	int				meal_count;
	t_data			*data;
}					t_philo;

int					ft_atoi(char *str);
long				get_timestamp(void);
int					init_forks(t_data *data);
int					init_philos(t_philo **philo, t_data *data);
int					destroy_forks(t_data *data, int i);
int					stop_philos(t_philo **philo, int i);
void				*routine(void *arg);
int					start_philos(t_philo **philo, t_data **data);
int					init_data(t_data *data);
void				parse_info(t_data *data, char **argv, int argc);
void				*ft_calloc(size_t nmemb, size_t size);
void				*fbi(void *arg);
int					rip_checker(t_data *data);
void				increment_meal_count(t_philo *philo);
#endif

/*
5 800 200 200
5 800 200 200 7
1 400 100 100
3 210 100 100
200 400 200 200 (died -> nothing after that)
Extreme edge case: 200 130 60 60 10
*/
