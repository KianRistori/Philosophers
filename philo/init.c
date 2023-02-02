/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:27:38 by kristori          #+#    #+#             */
/*   Updated: 2023/02/02 14:33:05 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init(t_philosopher *philosophers, pthread_mutex_t *forks,
				int argc, char **argv)
{
	t_philosopher	philo;
	int				i;

	philo.num_philosophers = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.num_eat = ft_atoi(argv[5]);
	else
		philo.num_eat = 0;
	i = 0;
	while (i < philo.num_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].times_eaten = 0;
		philosophers[i].time_to_die = philo.time_to_die;
		philosophers[i].time_to_eat = philo.time_to_eat;
		philosophers[i].time_to_sleep = philo.time_to_sleep;
		philosophers[i].num_philosophers = philo.num_philosophers;
		philosophers[i].num_eat = philo.num_eat;
		philosophers[i].forks = forks;
		i++;
	}
}
