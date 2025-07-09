/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:07:23 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/04 17:50:56 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define N_PHILO 5
# define EAT_TIME 1000
# define SLEEP_TIME 1000
# define THINK_TIME 1000

typedef struct s_data
{
	pthread_mutex_t	forks[N_PHILO];
	pthread_mutex_t	print_mutex;
	long			start_time;
}	t_data;

typedef struct s_philo
{
	int		id;
	t_data	*data;
	long	last_meal_time;
}	t_philo;

void	*philosopher_routine(void *arg);
void	print_action(t_philo *philo, const char *msg);
long	get_time_ms(void);

#endif
