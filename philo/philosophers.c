/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:24:39 by kristori          #+#    #+#             */
/*   Updated: 2023/01/31 12:03:33 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher(void *arg)
{
	t_philosopher *phil = (t_philosopher *)arg;

	while (1)
	{
		if (phil->times_eaten * (phil->time_to_eat + phil->time_to_sleep) >= phil->time_to_die)
		{
			printf("Philosopher %d has died\n", phil->id);
			return NULL;
		}

		if (phil->num_eat != 0 && phil->times_eaten >= phil->num_eat)
		{
			printf("All philosophers have eaten enough\n");
			return NULL;
		}

		pthread_mutex_lock(phil->forks + phil->id);
		pthread_mutex_lock(phil->forks + (phil->id + 1) % phil->num_philosophers);

		printf("Philosopher %d has taken a fork\n", phil->id);
		printf("Philosopher %d is eating\n", phil->id);
		usleep(phil->time_to_die * 1000);
		printf("Philosopher %d has finished eating\n", phil->id);
		phil->times_eaten++;

		pthread_mutex_unlock(phil->forks + (phil->id + 1) % phil->num_philosophers);
		pthread_mutex_unlock(phil->forks + phil->id);

		printf("Philosopher %d is sleeping\n", phil->id);
		usleep(phil->time_to_sleep * 1000);
	}
}

int main(int argc, char **argv) {
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
		pthread_create(&philosophers[i].thread, NULL, philosopher, &philosophers[i]);

	for (int i = 0; i < numPhilosophers; i++)
		pthread_join(philosophers[i].thread, NULL);

	return 0;
}
