/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/04 18:02:55 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_data *data, const char *msg, int id)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("Philosopher %d %s\n", id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)arg;
	left = philo->id;
	right = (philo->id + 1) % N_PHILO;
	safe_print(philo->data, "is thinking", philo->id);
	usleep(THINK_TIME);
	pthread_mutex_lock(&philo->data->forks[left]);
	safe_print(philo->data, "has taken left fork", philo->id);
	pthread_mutex_lock(&philo->data->forks[right]);
	safe_print(philo->data, "has taken right fork", philo->id);
	safe_print(philo->data, "is eating", philo->id);
	usleep(EAT_TIME);
	safe_print(philo->data, "is sleeping", philo->id);
	usleep(SLEEP_TIME);
	safe_print(philo->data, "has finished", philo->id);
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[N_PHILO];
	t_philo		philos[N_PHILO];
	t_data		data;
	int		i;

	pthread_mutex_init(&data.print_mutex, NULL);
	i = 0;
	while (i < N_PHILO)
		pthread_mutex_init(&data.forks[i++], NULL);
	i = 0;
	while (i < N_PHILO)
	{
		philos[i].id = i + 1;
		philos[i].data = &data;
		if (pthread_create(&threads[i], NULL,
				philosopher_routine, &philos[i]) != 0)
		{
			fprintf(stderr, "Failed to create thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < N_PHILO)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < N_PHILO)
		pthread_mutex_destroy(&data.forks[i++]);
	pthread_mutex_destroy(&data.print_mutex);
	return (0);
}
