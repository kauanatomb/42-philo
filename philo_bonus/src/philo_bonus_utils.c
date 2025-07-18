/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
		return (1);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (1);
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	if (data->death == SEM_FAILED)
		return (1);
	return (0);
}

static void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].last_meal_time = data->start_time;
		philos[i].n_meals = 0;
		i++;
	}
}

int	init_data_and_philos(t_data *data, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * data->n_philo);
	data->pids = malloc(sizeof(pid_t) * data->n_philo);
	if (!*philos || !data->pids)
		return (1);
	init_philos(data, *philos);
	data->start_time = get_time_ms();
	return (0);
}
