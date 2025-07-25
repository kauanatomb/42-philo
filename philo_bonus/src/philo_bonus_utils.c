/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/25 16:42:03 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/meal");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
		return (1);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (1);
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	if (data->death == SEM_FAILED)
		return (1);
	data->meal = sem_open("/meal", O_CREAT, 0644, 0);
	if (data->meal == SEM_FAILED)
		return (1);
	return (0);
}

int	init_allocs(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * data->n_philo);
	data->pids = malloc(sizeof(pid_t) * data->n_philo);
	if (!*philos || !data->pids)
		return (1);
	data->start_time = get_time_ms();
	while (i < data->n_philo)
	{
		(*philos)[i].id = i;
		(*philos)[i].data = data;
		(*philos)[i].n_meals = 0;
		(*philos)[i].last_meal_time = data->start_time;
		i++;
	}
	return (0);
}

int	start_processes(t_data *data, t_philo *philos)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->n_philo)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		else if (pid == 0)
		{
			philosopher_routine(&philos[i]);
			exit(0);
		}
		data->pids[i] = pid;
		i++;
	}
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit_error("gettimeofday() error", 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_usleep(long milliseconds)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(250);
}
