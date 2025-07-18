/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rollback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:12:52 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	return (1);
}

void	fail_aloc(pthread_mutex_t *forks, t_philo *philos, pthread_t *threads)
{
	if (forks)
		free(forks);
	if (philos)
		free(philos);
	if (threads)
		free(threads);
}

void	fail_mutex(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (forks > 0)
	{
		i = -1;
		while (++i < data->n_philo)
			pthread_mutex_destroy(&forks[i]);
	}
	pthread_mutex_destroy(&data->state_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}
