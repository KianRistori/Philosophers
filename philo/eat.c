/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:57 by kristori          #+#    #+#             */
/*   Updated: 2023/02/09 16:27:22 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_left(t_philosopher *philo)
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

void	ft_eat_right(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right);
	ft_print_active(philo->id, philo->params, "has taken right fork");
	pthread_mutex_lock(philo->left);
	ft_print_active(philo->id, philo->params, "has taken left fork");
	pthread_mutex_lock(&philo->params->eating);
	ft_print_active(philo->id, philo->params, "is eating");
	philo->last_meal = ft_get_time() - philo->params->start_time;
	pthread_mutex_unlock(&philo->params->eating);
	usleep(philo->params->time_to_eat * 1000);
	philo->meals_count++;
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}
