/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:40:50 by kristori          #+#    #+#             */
/*   Updated: 2023/02/01 15:08:25 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	ris;
	int	sign;

	if (!str)
		return (0);
	ris = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ris = ris * 10 + *str - '0';
		str++;
	}
	return (ris * sign);
}

long long	ft_current_timestamp(struct timeval *start)
{
	struct timeval	te;
	long long		now;
	long long		start_milliseconds;

	gettimeofday(&te, NULL);
	start_milliseconds = start->tv_sec * 1000LL + start->tv_usec / 1000;
	now = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (now - start_milliseconds);
}

int	ft_error_argv(void)
{
	printf("Not enough arguments provided\n");
	return (1);
}
