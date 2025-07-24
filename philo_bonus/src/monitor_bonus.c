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

void	check_death(t_philo *philo)
{
	long	now;
	long	time_since_meal;

	while (1)
	{
		sem_wait(philo->data->death);
		now = get_time_ms();
		time_since_meal = now - philo->last_meal_time;
		if (time_since_meal > philo->data->time_to_die)
		{
			print_action(philo, "died");
			sem_wait(philo->data->print);
			sem_post(philo->data->meal);
			exit(0);
		}
		sem_post(philo->data->death);
	}
}

void	*meal_checker(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i = 0;

	while (1)
	{
		sem_wait(data->meal);
		++i;
		if (i >= data->n_philo)
		{
			kill_all_processes(data);
			cleanup_resources(data, NULL, NULL, 0);
		}
	}
}
