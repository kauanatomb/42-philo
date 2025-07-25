/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_death(t_philo *philo)
{
	long	now = get_time_ms();
	long	time_since_meal;

	sem_wait(philo->data->meal);
	time_since_meal = now - philo->last_meal_time;
	sem_post(philo->data->meal);

	if (time_since_meal > philo->data->time_to_die)
	{
		print_action(philo, "died");
		set_simulation_stop(philo->data);
		exit(1);
	}
	return (0);
}

static int	check_meals(t_philo *philo)
{
	sem_wait(philo->data->meal);
	int done = (philo->data->must_eat_count > 0
			&& philo->n_meals >= philo->data->must_eat_count);
	sem_post(philo->data->meal);

	if (done)
	{
		set_simulation_stop(philo->data);
		return (1);
	}
	return (0);
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (1)
	{
		safe_usleep(1);
		if (check_death(philo) || check_meals(philo))
			break;
	}
	exit(0);
}
