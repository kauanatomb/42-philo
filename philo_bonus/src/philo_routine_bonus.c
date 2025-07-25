/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/25 16:40:45 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->death);
	philo->last_meal_time = get_time_ms();
	philo->n_meals++;
	sem_post(philo->data->death);
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
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, ft_monitor, philo) != 0
		|| pthread_detach(monitor) != 0)
		exit(EXIT_FAILURE);
	if (philo->id % 2 == 0)
		safe_usleep(10);
	while (1)
	{
		if (philo->finished)
		{
			safe_usleep(100);
			continue ;
		}
		eat(philo);
		dream(philo);
		think(philo);
	}
	exit(0);
}
