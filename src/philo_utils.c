/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/09 18:02:55 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("time: %ld philo: %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	release_forks(t_philo *philo, int f1, int f2)
{
	pthread_mutex_unlock(&philo->data->forks[f1]);
	pthread_mutex_unlock(&philo->data->forks[f2]);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	int		left = philo->id;
	int		right = (philo->id + 1) % philo->data->n_philo;

	int		first = left < right ? left : right;
	int		second = left < right ? right : left;

	while (!is_simulation_stopped(philo->data))
	{
		print_action(philo, "is thinking");
		usleep(THINK_TIME);

		pthread_mutex_lock(&philo->data->forks[first]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[second]);
		print_action(philo, "has taken a fork");

		if (is_simulation_stopped(philo->data))
		{
			release_forks(philo, first, second);
			pthread_exit(NULL);
		}

		philo->last_meal_time = get_time_ms();
		print_action(philo, "is eating");
		usleep(EAT_TIME);

		release_forks(philo, first, second);
		print_action(philo, "is sleeping");
		usleep(SLEEP_TIME);
	}
	return (NULL);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
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

void	*monitor_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_data *data = philos[0].data;
	int		i;

	while (!is_simulation_stopped(data))
	{
		i = 0;
		while (i < N_PHILO)
		{
			long now = get_time_ms();
			if (now - philos[i].last_meal_time > data->time_to_die)
			{
				print_action(&philos[i], "died");
				set_simulation_stop(data);
				return NULL;
			}
			i++;
		}
		usleep(100); // Evita busy waiting (checa a cada 100µs)
	}
	return NULL;
}
