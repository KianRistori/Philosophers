/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:31 by kristori          #+#    #+#             */
/*   Updated: 2023/02/08 15:32:58 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	ft_print_active(philo->id, philo->params, "has taken left fork");
	pthread_mutex_lock(philo->right);
	ft_print_active(philo->id, philo->params, "has taken right fork");
	pthread_mutex_lock(&philo->params->eating);
	ft_print_active(philo->id, philo->params, "is eating");
	philo->last_meal = ft_get_time() - philo->params->start_time;
	pthread_mutex_unlock(&philo->params->eating);
	usleep(philo->params->time_to_eat * 1000);
	philo->meals_count++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*ft_philo_life(void *args)
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

void	ft_end_routine(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->num_of_philo)
	{
		pthread_join(params->philosophers[i].thread_philo, NULL);
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

int	ft_routine(t_param *params)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = params->philosophers;
	params->start_time = ft_get_time();
	while (i < params->num_of_philo)
	{
		if (pthread_create(&philo[i].thread_philo, NULL, ft_philo_life, &philo[i]))
			return (ft_error(3));
		i++;
	}
	ft_checker(params);
	ft_end_routine(params);
	return (0);
}

int	main(int argc, char **argv)
{
	t_param		params;

	if (ft_get_params(argc, argv, &params))
		return (1);
	if (ft_init_mutex(&params))
		return (1);
	if (ft_init_philo(&params))
		return (1);
	if (ft_routine(&params))
		return (1);
	return (0);
}
