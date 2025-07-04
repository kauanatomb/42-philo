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

void	safe_print(pthread_mutex_t *mutex, const char *msg, int id)
{
	pthread_mutex_lock(mutex);
	printf("Philosopher %d %s\n", id, msg);
	pthread_mutex_unlock(mutex);
}

void	*philosopher_routine(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	safe_print(args->print_mutex, "is thinking", args->id);
	usleep(THINK_TIME);
	safe_print(args->print_mutex, "is eating", args->id);
	usleep(EAT_TIME);
	safe_print(args->print_mutex, "is sleeping", args->id);
	usleep(SLEEP_TIME);
	safe_print(args->print_mutex, "has finished", args->id);
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[N_PHILO];
	t_args		args[N_PHILO];
	pthread_mutex_t	print_mutex;
	int		i;

	pthread_mutex_init(&print_mutex, NULL);
	i = 0;
	while (i < N_PHILO)
	{
		args[i].id = i + 1;
		args[i].print_mutex = &print_mutex;
		if (pthread_create(&threads[i], NULL,
				philosopher_routine, &args[i]) != 0)
		{
			fprintf(stderr, "Failed to create thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < N_PHILO)
		pthread_join(threads[i++], NULL);
	pthread_mutex_destroy(&print_mutex);
	return (0);
}
