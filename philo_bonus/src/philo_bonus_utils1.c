/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	if (philo->data->n_philo == 1)
	{
		safe_usleep(philo->data->time_to_die);
		sem_post(philo->data->forks);
		exit(1);
	}
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");

	sem_wait(philo->data->meal);
	philo->last_meal_time = get_time_ms();
	philo->n_meals++;
	sem_post(philo->data->meal);

	print_action(philo, "is eating");
	safe_usleep(philo->data->time_to_eat);

	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

static void	dream(t_philo *philo)
{
	print_action(philo, "is sleeping");
	safe_usleep(philo->data->time_to_sleep);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t monitor;

	if (pthread_create(&monitor, NULL, philo_monitor, philo) != 0)
		exit(1);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		safe_usleep(10);
	while (!is_simulation_stopped(philo->data))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	exit(0);
}

int	is_simulation_stopped(t_data *data)
{
	int stopped;

	sem_wait(&data->death);
	stopped = data->stop_flag;
	sem_post(&data->death);
	return stopped;
}

void	set_simulation_stop(t_data *data)
{
	sem_wait(&data->death);
	data->stop_flag = 1;
	sem_post(&data->death);
}
