/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:38 by kristori          #+#    #+#             */
/*   Updated: 2023/02/09 16:27:44 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philoshpher {
	int				id;
	int				meals_count;
	long			last_meal;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_t		thread;
	struct s_param	*params;
}		t_philosopher;

typedef struct s_param {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				is_dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	printing;
	t_philosopher	*philosophers;
}				t_param;

int		ft_atoi(const char *str);
int		ft_init_params(int argc, char **argv, t_param *params);
int		ft_init_mutex(t_param *param);
int		ft_init_philo(t_param *params);
long	ft_get_time(void);
void	ft_print_active(int id, t_param *param, char *str);
void	ft_print_death(int id, t_param *param, char *str);
void	ft_checker(t_param *params);
void	ft_check_num_eat(t_param *params);
void	ft_eat_left(t_philosopher *philo);
void	ft_eat_right(t_philosopher *philo);

#endif
