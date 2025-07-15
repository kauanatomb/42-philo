/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_usleep(long milliseconds)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(250);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->n_philo == 1)
	{
		safe_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->n_meals++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	safe_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		safe_usleep(10);
	while (!is_simulation_stopped(philo->data))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}
