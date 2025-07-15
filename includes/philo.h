/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:07:23 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 17:19:39 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				stop;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	t_data			*data;
	long			last_meal_time;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

int		init_forks_mutex(t_data *data, pthread_mutex_t *forks);
int		init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks);
int		start_threads(t_data *data, t_philo *philos, pthread_t *threads);
void	cleanup(t_data *data, t_philo *philos,
			pthread_t *threads, pthread_mutex_t *forks);
void	join_all(t_data *data, pthread_t *threads, pthread_t monitor);

int		parse_args(int argc, char **argv, t_data *data);
int		exit_error(char *msg);
void	*philosopher_routine(void *arg);
void	print_action(t_philo *philo, const char *msg);
long	get_time_ms(void);
void	*monitor_routine(void *arg);
int		is_simulation_stopped(t_data *data);
void	set_simulation_stop(t_data *data);
void	safe_usleep(long milliseconds);

#endif
