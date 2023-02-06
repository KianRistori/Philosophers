/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:34:12 by kristori          #+#    #+#             */
/*   Updated: 2023/02/06 12:44:07 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_philosopher {
	int				id;
	int				times_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philosophers;
	int				num_eat;
	int				run;
	struct timeval	last_eaten;
	pthread_mutex_t	*forks;
	pthread_mutex_t *times_eaten_mutex;
	pthread_mutex_t *run_mutex;
	pthread_t		thread;
}			t_philosopher;



void		ft_init(t_philosopher *philosophers, pthread_mutex_t *forks,
				int argc, char **argv);
void	ft_init_2(t_philosopher *philosophers, pthread_mutex_t *times_eaten_mutex, pthread_mutex_t *run_mutex);
void		*ft_philosopher(void *arg);
int			ft_atoi(const char *str);
long long	ft_current_timestamp(struct timeval *start);
int			ft_error_argv(void);

#endif
