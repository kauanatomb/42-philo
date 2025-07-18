/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/18 11:50:16 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all_mutexes(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].last_meal_time = data->start_time;
		philos[i].n_meals = 0;
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % data->n_philo];
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_threads(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&threads[i], NULL,
				philosopher_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	join_all(t_data *data, pthread_t *threads, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	cleanup(t_data *data, t_philo *philos,
	pthread_t *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->state_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(threads);
	free(forks);
	free(philos);
}
