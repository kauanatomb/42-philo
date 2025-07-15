/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:07:23 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 14:56:07 by ktombola         ###   ########.fr       */
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

int		parse_args(int argc, char **argv, t_data *data);
int		exit_error(char *msg);
void	*philosopher_routine(void *arg);
void	print_action(t_philo *philo, const char *msg);
long	get_time_ms(void);
void	*monitor_routine(void *arg);
int		is_simulation_stopped(t_data *data);
void	safe_usleep(long milliseconds);

#endif
