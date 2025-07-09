/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/09 18:02:55 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("time: %ld philo: %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		first = philo->id;
		second = (philo->id + 1) % N_PHILO;
	}
	else
	{
		first = (philo->id + 1) % N_PHILO;
		second = philo->id;
	}
	print_action(philo, "is thinking");
	usleep(THINK_TIME);
	pthread_mutex_lock(&philo->data->forks[first]);
	print_action(philo, "has taken left fork");
	pthread_mutex_lock(&philo->data->forks[second]);
	print_action(philo, "has taken right fork");
	print_action(philo, "is eating");
    philo->last_meal_time = get_time_ms();
	usleep(EAT_TIME);
	print_action(philo, "is sleeping");
	usleep(SLEEP_TIME);
	print_action(philo, "has finished");
	return (NULL);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
