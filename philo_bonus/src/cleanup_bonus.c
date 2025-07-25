/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:00:51 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	exit_error(char *msg, int signal)
{
	if (msg)
		fprintf(stderr, "%s\n", msg);
	return (signal);
}

void	cleanup_semaphores(t_data *data)
{
	if (data->forks != SEM_FAILED)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
	}
	if (data->print != SEM_FAILED)
	{
		sem_close(data->print);
		sem_unlink("/print");
	}
	if (data->death != SEM_FAILED)
	{
		sem_close(data->death);
		sem_unlink("/death");
	}
	if (data->meal != SEM_FAILED)
	{
		sem_close(data->meal);
		sem_unlink("/meal");
	}
}

void	cleanup_resources(t_data *data, t_philo *philos, char *msg, int signal)
{
	cleanup_semaphores(data);
	if (data->pids)
		free(data->pids);
	if (philos)
		free(philos);
	exit_error(msg, signal);
}