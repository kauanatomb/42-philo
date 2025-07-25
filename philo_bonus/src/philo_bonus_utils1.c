/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils1.c                               :+:      :+:    :+:   */
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
	int			current_meals;
	int			must_eat;

	if (pthread_create(&monitor, NULL, ft_monitor, philo) != 0
		|| pthread_detach(monitor) != 0)
		exit(EXIT_FAILURE);
	if (philo->id % 2 == 0)
		safe_usleep(10);
	while (1)
	{
		sem_wait(philo->data->death);
		current_meals = philo->n_meals;
		must_eat = philo->data->must_eat_count;
		sem_post(philo->data->death);
		if (must_eat > 0 && current_meals >= must_eat)
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
