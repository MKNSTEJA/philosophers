/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:02 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/07 13:07:48 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *fbi(void *arg)
{
    t_philo *philo = (t_philo *) arg;
    t_data *data = philo[0].data;
    int i = 0;

    while(data->stop == 0)
    {
        while(i < data->num)
        {
            if(get_timestamp() - philo[0].last_meal_time`)
        }
    }
}
