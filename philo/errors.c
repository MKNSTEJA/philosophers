/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:49:12 by kmummadi          #+#    #+#             */
/*   Updated: 2025/04/02 16:22:12 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	num_checker(char *str);

int	errors(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = ft_atoi(argv[i]);
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments!\n");
		return (-1);
	}
	if (num < 0 || num > 200)
		return (printf("Invalid number of philos!\n"), -1);
	while (i < argc)
	{
		if (num_checker(argv[i]) == -1)
		{
			printf("Invalid input!\n");
			return (-1);
		}
		if (ft_strncmp(argv[i], "2147483647", ft_strlen("2147483647")) > 0)
			return (printf("Only integers!\n"), -1);
		i++;
	}
	return (0);
}

int	num_checker(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (!(str[j] >= '0' && str[j] <= '9'))
			return (-1);
		j++;
	}
	return (0);
}
