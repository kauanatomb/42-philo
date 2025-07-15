/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:12:52 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_t		monitor;

	if (parse_args(argc, argv, &data))
		return (exit_error("Invalid arguments."));
	data.stop = 0;
	data.start_time = get_time_ms();
	pthread_mutex_init(&data.state_mutex, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);
	forks = malloc(sizeof(pthread_mutex_t) * data.n_philo);
	philos = malloc(sizeof(t_philo) * data.n_philo);
	threads = malloc(sizeof(pthread_t) * data.n_philo);
	if (!forks || !philos || !threads
		|| init_forks_mutex(&data, forks)
		|| init_philos(&data, philos, forks)
		|| start_threads(&data, philos, threads)
		|| pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (exit_error("Initialization failed"));
	join_all(&data, threads, monitor);
	cleanup(&data, philos, threads, forks);
	return (0);
}
