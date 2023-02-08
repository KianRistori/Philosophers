/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:08:38 by kristori          #+#    #+#             */
/*   Updated: 2023/02/08 15:31:19 by kristori         ###   ########.fr       */
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
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread_philo;
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
}		t_param;

int		ft_atoi(const char *str);
int		ft_error(int err);
long	ft_get_time(void);
int		ft_get_params(int argc, char **argv, t_param *params);
int		ft_init_mutex(t_param *param);
int		ft_init_philo(t_param *params);
void	ft_print_active(int id, t_param *param, char *str);
void	ft_print_death(int id, t_param *param, char *str);
void	ft_checker(t_param *params);
void	ft_check_num_of_eat(t_param *params);

#endif
