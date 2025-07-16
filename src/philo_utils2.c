/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:08:52 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - (long)philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_simulation_stopped(philo->data))
		printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit_error("gettimeofday() error");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_simulation_stopped(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->state_mutex);
	return (stop);
}

void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->state_mutex);
}
