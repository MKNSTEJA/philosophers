/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:24:53 by kmummadi          #+#    #+#             */
/*   Updated: 2025/02/11 10:15:51 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *string, size_t range)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)string;
	i = 0;
	while (i < range)
	{
		str[i] = 0;
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	answer;

	i = 0;
	neg = 1;
	answer = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == '\v'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		answer = answer * 10 + (str[i] - '0');
		i++;
	}
	return (answer * neg);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;

	pointer = malloc(size * nmemb);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, nmemb * size);
	return (pointer);
}
