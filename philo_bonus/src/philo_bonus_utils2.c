/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - (long)philo->data->start_time;
	if (!is_simulation_stopped(philo->data))
	{
		sem_wait(philo->data->print);
		printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
		sem_post(philo->data->print);
	}
}