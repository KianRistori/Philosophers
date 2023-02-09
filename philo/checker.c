/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:58 by kristori          #+#    #+#             */
/*   Updated: 2023/02/09 15:21:18 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_check_num_eat(t_param *params)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (i < params->num_of_philo)
	{
		if (params->philosophers->meals_count > params->num_of_eat)
			ct++;
		i++;
	}
	if (ct == params->num_of_philo)
		params->is_dead = 0;
}

void	ft_checker(t_param *params)
{
	int	i;

	while (params->is_dead)
	{
		i = 0;
		while (i < params->num_of_philo && params->is_dead)
		{
			pthread_mutex_lock(&params->eating);
			if (ft_get_time() - params->start_time
				- params->philosophers[i].last_meal
				> params->time_to_die)
				ft_print_death(i, params, "died");
			pthread_mutex_unlock(&params->eating);
			usleep(100);
			i++;
		}
		if (params->num_of_eat != -1 && params->is_dead)
			ft_check_num_eat(params);
	}
}
