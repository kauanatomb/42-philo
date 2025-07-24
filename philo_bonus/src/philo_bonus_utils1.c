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
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	sem_wait(philo->data->death);
	philo->last_meal_time = get_time_ms();
	philo->n_meals++;
	sem_post(philo->data->death);
	if (philo->data->must_eat_count > 0 &&
		philo->n_meals >= philo->data->must_eat_count)
		sem_post(philo->data->meal);
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

	if (pthread_create(&monitor, NULL, (void *)check_death, philo) != 0
		|| pthread_detach(monitor) != 0)
		exit(1);
	while (1)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
}
