/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:07:23 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/25 16:48:47 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data {
	int			n_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long		start_time;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*death;
	sem_t		*meal;
	pid_t		*pids;
}		t_data;

typedef struct s_philo {
	int		id;
	int		n_meals;
	long	last_meal_time;
	t_data	*data;
}	t_philo;

int		init_semaphores(t_data *data);
int		init_allocs(t_data *data, t_philo **philos);
void	cleanup_semaphores(t_data *data);
void	cleanup_resources(t_data *data, t_philo *philos, char *msg, int signal);

int		parse_args(int argc, char **argv, t_data *data);
int		exit_error(char *msg, int signal);
long	get_time_ms(void);

void	philosopher_routine(t_philo *philo);
void	print_action(t_philo *philo, const char *msg);
int		start_processes(t_data *data, t_philo *philos);
void	*ft_monitor(void *arg);
void	wait_for_termination(t_data *data);
void	safe_usleep(long milliseconds);
void	kill_all_processes(t_data *data);

#endif
