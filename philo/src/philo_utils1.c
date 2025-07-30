/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/28 11:54:01 by ktombola         ###   ########.fr       */
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

static int	should_stop_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->must_eat_count > 0
		&& philo->n_meals >= philo->data->must_eat_count)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static void	eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (should_stop_eating(philo))
		return ;
	if (first > second)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (philo->data->n_philo == 1)
	{
		safe_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(first);
		return ;
	}
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->n_meals++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	safe_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		safe_usleep(10);
	first = philo->r_fork;
	second = philo->l_fork;
	while (!is_simulation_stopped(philo->data))
	{
		eat(philo, first, second);
		print_action(philo, "is sleeping");
		safe_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
