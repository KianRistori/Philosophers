/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:22 by kristori          #+#    #+#             */
/*   Updated: 2023/02/08 15:31:22 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_params(const t_param *params)
{
	if (params->num_of_philo == 1)
	{
		printf("Incorrect number of philosophers\n");
		return (1);
	}
	return (0);
}

int	ft_get_params(int argc, char **argv, t_param *params)
{
	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	params->num_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->is_dead = 1;
	if (argc == 6)
		params->num_of_eat = ft_atoi(argv[5]);
	else
		params->num_of_eat = -1;
	return (ft_check_params(params));
}

int	ft_init_mutex(t_param *param)
{
	int	i;

	param->forks = malloc(sizeof(pthread_mutex_t) * param->num_of_philo);
	if (param->forks == NULL)
		return (ft_error(1));
	i = 0;
	while (i < param->num_of_philo)
	{
		if (pthread_mutex_init(&param->forks[i], NULL))
			return (ft_error(2));
		i++;
	}
	if (pthread_mutex_init(&param->eating, NULL))
		return (ft_error(2));
	if (pthread_mutex_init(&param->printing, NULL))
		return (ft_error(2));
	return (0);
}

int	ft_init_philo(t_param *params)
{
	int	i;

	params->philosophers = malloc(sizeof(t_philosopher) * params->num_of_philo);
	if (params->philosophers == NULL)
		return (ft_error(1));
	i = 0;
	while (i < params->num_of_philo)
	{
		params->philosophers[i].id = i;
		params->philosophers[i].meals_count = 0;
		params->philosophers[i].last_meal = 0;
		params->philosophers[i].params = params;
		params->philosophers[i].left = &params->forks[i];
		if (i < params->num_of_philo - 1)
			params->philosophers[i].right = &params->forks[i + 1];
		else
			params->philosophers[i].right = &params->forks[0];
		i++;
	}
	return (0);
}
