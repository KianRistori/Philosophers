/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:24:39 by kristori          #+#    #+#             */
/*   Updated: 2023/01/31 15:38:27 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosopher(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;
	struct timeval	start;
	gettimeofday(&start, NULL);

	while (1)
	{
		if (philo->times_eaten * (philo->time_to_eat + philo->time_to_sleep) >= philo->time_to_die)
		{
			printf("%lldms %d has died\n", ft_current_timestamp(&start), philo->id);
			return NULL;
		}

		if (philo->num_eat != 0 && philo->times_eaten >= philo->num_eat)
		{
			printf("All philosophers have eaten enough\n");
			return NULL;
		}

		pthread_mutex_lock(philo->forks + philo->id);
		pthread_mutex_lock(philo->forks + (philo->id + 1) % philo->num_philosophers);

		printf("%lldms %d has taken a fork\n", ft_current_timestamp(&start), philo->id);
		printf("%lldms %d is eating\n", ft_current_timestamp(&start), philo->id);
		usleep(philo->time_to_die * 1000);
		printf("%lldms %d has finished eating\n", ft_current_timestamp(&start), philo->id);
		philo->times_eaten++;

		pthread_mutex_unlock(philo->forks + (philo->id + 1) % philo->num_philosophers);
		pthread_mutex_unlock(philo->forks + philo->id);

		printf("%lldms %d is sleeping\n", ft_current_timestamp(&start), philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("%lldms %d is thinking\n", ft_current_timestamp(&start), philo->id);
	}
}

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Not enough arguments provided\n");
		return 1;
	}

	int numPhilosophers = ft_atoi(argv[1]);
	int timeToDie = ft_atoi(argv[2]);
	int timeToEat = ft_atoi(argv[3]);
	int timeToSleep = ft_atoi(argv[4]);
	int numEat = (argc == 6) ? ft_atoi(argv[5]) : 0;

	pthread_mutex_t forks[numPhilosophers];
	for (int i = 0; i < numPhilosophers; i++)
		pthread_mutex_init(forks + i, NULL);

	t_philosopher philosophers[numPhilosophers];
	for (int i = 0; i < numPhilosophers; i++)
	{
		philosophers[i].id = i;
		philosophers[i].times_eaten = 0;
		philosophers[i].time_to_die = timeToDie;
		philosophers[i].time_to_eat = timeToEat;
		philosophers[i].time_to_sleep = timeToSleep;
		philosophers[i].num_philosophers = numPhilosophers;
		philosophers[i].num_eat = numEat;
		philosophers[i].forks = forks;
	}

	for (int i = 0; i < numPhilosophers; i++)
		pthread_create(&philosophers[i].thread, NULL, ft_philosopher, &philosophers[i]);

	for (int i = 0; i < numPhilosophers; i++)
		pthread_join(philosophers[i].thread, NULL);

	for (int i = 0; i < numPhilosophers; i++)
		pthread_mutex_destroy(&forks[i]);

	return 0;
}
