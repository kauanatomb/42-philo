/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:07:23 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 17:19:39 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data {
    int             n_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    long            start_time;
    sem_t           *forks;
    sem_t           *print;
    sem_t           *death;
    pid_t           *pids;
} t_data;

typedef struct s_philo {
    int             id;
    int             n_meals;
    long            last_meal_time;
    t_data          *data;
} t_philo;

int		init_semaphores(t_data *data);
int	    init_data_and_philos(t_data *data, t_philo **philos);
void	cleanup_semaphores(t_data *data);
void	cleanup_resources(t_data *data, t_philo *philos);

int		parse_args(int argc, char **argv, t_data *data);
int		exit_error(char *msg);
long	get_time_ms(void);


void	*philosopher_routine(void *arg);
void	print_action(t_philo *philo, const char *msg);
void	*monitor_routine(void *arg);
int		is_simulation_stopped(t_data *data);
void	set_simulation_stop(t_data *data);
void	safe_usleep(long milliseconds);

#endif
