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

void	philosopher_routine(t_data *data, int id)
{
	t_philo philo;

	philo.id = id;
	philo.data = data;
	philo.last_meal_time = data->start_time;
	philo.n_meals = 0;

	if (id % 2 == 0)
		safe_usleep(10);
	while (!is_simulation_stopped(data))
	{
		eat(&philo);
		dream(&philo);
		think(&philo);
	}
	exit(0);
}
