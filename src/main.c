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

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_mutex_t	*forks;
	pthread_t	monitor_thread;
	int			i;

	if (parse_args(argc, argv, &data))
		return (exit_error("Invalid arguments."));

	data.stop = 0;
	data.start_time = get_time_ms();
	pthread_mutex_init(&data.state_mutex, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);

	forks = malloc(sizeof(pthread_mutex_t) * data.n_philo);
	philos = malloc(sizeof(t_philo) * data.n_philo);
	threads = malloc(sizeof(pthread_t) * data.n_philo);
	if (!forks || !philos || !threads)
		return (exit_error("Malloc failed"));

	i = -1;
	while (++i < data.n_philo)
		pthread_mutex_init(&forks[i], NULL);

	i = -1;
	while (++i < data.n_philo)
	{
		philos[i].id = i;
		philos[i].data = &data;
		philos[i].last_meal_time = data.start_time;
		philos[i].n_meals = 0;
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % data.n_philo];
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		if (pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]) != 0)
			return (exit_error("Thread creation failed"));
	}

	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
		return (exit_error("Monitor thread creation failed"));

	i = -1;
	while (++i < data.n_philo)
		pthread_join(threads[i], NULL);

	pthread_join(monitor_thread, NULL);

	i = -1;
	while (++i < data.n_philo)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data.state_mutex);
	pthread_mutex_destroy(&data.print_mutex);
	free(forks);
	free(philos);
	free(threads);
	return (0);
}

