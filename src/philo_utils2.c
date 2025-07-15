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
		printf("%ld %d %s\n", timestamp, philo->id, msg);
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

static int	check_death(t_philo *philos)
{
	t_data	*data;
	long	now;
	long	last_meal;
	int		i;
	
	data = philos[0].data;
	i = 0;
	while (i < data->n_philo)
	{
		now = get_time_ms();
		pthread_mutex_lock(&philos[i].meal_mutex);
		last_meal = philos[i].last_meal_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (now - last_meal > data->time_to_die)
		{
			print_action(&philos[i], "died");
			set_simulation_stop(data);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_ate(t_philo *philos)
{
	t_data	*data;
	int		i;
	
	data = philos[0].data;
	if (data->must_eat_count <= 0)
		return (0);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].n_meals < data->must_eat_count)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	set_simulation_stop(data);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	
	philos = (t_philo *)arg;
	while (!is_simulation_stopped(philos[0].data))
	{
		if (check_death(philos) || check_all_ate(philos))
			break;
		safe_usleep(1);
	}
	return (NULL);
}
