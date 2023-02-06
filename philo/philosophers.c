/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:24:39 by kristori          #+#    #+#             */
/*   Updated: 2023/02/06 12:51:01 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosopher(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;
	struct timeval	start, current;
	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	gettimeofday(&philo->last_eaten, NULL);
	while (1)
	{
		if (philo[philo->id].run == 1)
			break ;
		if ((philo->times_eaten >= philo->num_eat) && (philo->num_eat != 0))
		{
			printf("%lldms %d has died\n", ft_current_timestamp(&start), philo->id);
			pthread_mutex_lock(philo->run_mutex + philo->id);
			philo[philo->id].run = 1;
			pthread_mutex_unlock(philo->run_mutex + philo->id);
			return (NULL);
		}
		gettimeofday(&current, NULL);
		long long int time_since_last_eat = (current.tv_sec - philo->last_eaten.tv_sec) * 1000LL +
			(current.tv_usec - philo->last_eaten.tv_usec) / 1000;
		if (time_since_last_eat >= philo->time_to_die)
		{
			printf("%lldms %d has died\n", ft_current_timestamp(&start), philo->id);
			pthread_mutex_lock(philo->run_mutex + philo->id);
			philo[philo->id].run = 1;
			pthread_mutex_unlock(philo->run_mutex + philo->id);
			return (NULL);
		}
		pthread_mutex_lock(philo->forks + philo->id);
		pthread_mutex_lock(philo->forks + (philo->id + 1) % philo->num_philosophers);
		printf("%lldms %d has taken a fork\n", ft_current_timestamp(&start), philo->id);
		printf("%lldms %d is eating\n", ft_current_timestamp(&start), philo->id);
		gettimeofday(&philo->last_eaten, NULL);
		usleep(philo->time_to_eat * 1000);
		printf("%lldms %d has finished eating\n", ft_current_timestamp(&start), philo->id);
		pthread_mutex_lock(philo->times_eaten_mutex + philo->id);
		philo->times_eaten++;
		pthread_mutex_unlock(philo->times_eaten_mutex + philo->id);
		pthread_mutex_unlock(philo->forks + (philo->id + 1) % philo->num_philosophers);
		pthread_mutex_unlock(philo->forks + philo->id);
		printf("%lldms %d is sleeping\n", ft_current_timestamp(&start), philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("%lldms %d is thinking\n", ft_current_timestamp(&start), philo->id);
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	int	num_philosophers;
	int	i;

	i = -1;
	if (argc < 5)
		return (ft_error_argv());
	num_philosophers = ft_atoi(argv[1]);
	t_philosopher *philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * num_philosophers + 1);
	pthread_mutex_t *forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philosophers + 1);
	pthread_mutex_t *times_eaten_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philosophers + 1);
	pthread_mutex_t *run_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philosophers + 1);
	while (++i < num_philosophers)
	{
		pthread_mutex_init(forks + i, NULL);
		pthread_mutex_init(times_eaten_mutex + i, NULL);
		pthread_mutex_init(run_mutex + i, NULL);
	}
	i = -1;
	ft_init(philosophers, forks, argc, argv);
	ft_init_2(philosophers, times_eaten_mutex, run_mutex);
	while (++i < num_philosophers)
		pthread_create(&philosophers[i].thread, NULL, ft_philosopher, &philosophers[i]);
	i = -1;
	while (++i < num_philosophers)
		pthread_join(philosophers[i].thread, NULL);
	i = -1;
	while (++i < num_philosophers)
		pthread_mutex_destroy(&forks[i]);
	free(philosophers);
	free(forks);
	return (0);
}
