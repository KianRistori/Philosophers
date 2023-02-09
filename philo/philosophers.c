/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:31 by kristori          #+#    #+#             */
/*   Updated: 2023/02/09 16:28:42 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		ft_eat_left(philo);
	else
		ft_eat_right(philo);
}

void	*ft_philo_routine(void *args)
{
	t_philosopher	*philo;
	t_param			*params;

	philo = (t_philosopher *) args;
	params = philo->params;
	if (philo->id % 2)
		usleep(20000);
	while (params->is_dead)
	{
		ft_philo_eat(philo);
		ft_print_active(philo->id, params, "is sleeping");
		usleep(params->time_to_sleep * 1000);
		ft_print_active(philo->id, params, "is thinking");
	}
	return (NULL);
}

void	ft_create_thread2(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->num_of_philo)
	{
		pthread_join(params->philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < params->num_of_philo)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->eating);
	pthread_mutex_destroy(&params->printing);
	free(params->forks);
	free(params->philosophers);
}

int	ft_create_thread(t_param *params)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = params->philosophers;
	params->start_time = ft_get_time();
	while (i < params->num_of_philo)
	{
		if (pthread_create(&philo[i].thread,
				NULL, ft_philo_routine, &philo[i]))
			return (1);
		i++;
	}
	ft_checker(params);
	ft_create_thread2(params);
	return (0);
}

int	main(int argc, char **argv)
{
	t_param		params;

	if (ft_init_params(argc, argv, &params))
		return (1);
	if (ft_init_mutex(&params))
		return (1);
	if (ft_init_philo(&params))
		return (1);
	if (ft_create_thread(&params))
		return (1);
	return (0);
}
