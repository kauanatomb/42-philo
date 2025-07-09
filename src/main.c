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
	data.start_time = get_time_ms();
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
		philos[i].last_meal_time = data.start_time;
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
