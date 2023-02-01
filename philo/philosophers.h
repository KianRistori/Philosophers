/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:34:12 by kristori          #+#    #+#             */
/*   Updated: 2023/02/01 15:08:43 by kristori         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_t		thread;
}			t_philosopher;

void		*ft_philosopher(void *arg);
int			ft_atoi(const char *str);
long long	ft_current_timestamp(struct timeval *start);
void		ft_init(t_philosopher *philosophers, pthread_mutex_t *forks,
				int argc, char **argv);
int			ft_error_argv(void);

#endif