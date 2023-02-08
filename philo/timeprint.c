/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timenprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:46 by kristori          #+#    #+#             */
/*   Updated: 2023/02/08 15:18:03 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print_active(int id, t_param *param, char *str)
{
	pthread_mutex_lock(&param->printing);
	if (param->is_dead)
		printf("%ldms %d %s\n", ft_get_time() - param->start_time, id + 1, str);
	pthread_mutex_unlock(&param->printing);
}

void	ft_print_death(int id, t_param *param, char *str)
{
	pthread_mutex_lock(&param->printing);
	if (param->is_dead)
		printf("%ldms %d %s\n", ft_get_time() - param->start_time, id + 1, str);
	param->is_dead = 0;
	pthread_mutex_unlock(&param->printing);
}
