/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/25 16:36:09 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	sem_wait(philo->data->print);
	timestamp = get_time_ms() - (long)philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
	sem_post(philo->data->print);
}

void	wait_for_termination(t_data *data)
{
	int	status;
	int	completed_count;

	completed_count = 0;
	if (data->must_eat_count > 0)
	{
		while (completed_count < data->n_philo)
		{
			sem_wait(data->meal);
			completed_count++;
		}
		kill_all_processes(data);
		return ;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_processes(data);
			break ;
		}
	}
}

void	kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
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
