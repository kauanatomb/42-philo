/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/25 16:25:03 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (parse_args(argc, argv, &data))
		return (exit_error("Invalid arguments.", 1));
	if (init_semaphores(&data))
	{
		cleanup_semaphores(&data);
		return (exit_error("Failed to init semaphores", 1));
	}
	if (init_allocs(&data, &philos))
		cleanup_resources(&data, philos, "Malloc failed", 1);
	if (start_processes(&data, philos) != 0)
	{
		kill_all_processes(&data);
		cleanup_resources(&data, philos, "Failed to start processes", 1);
	}
	wait_for_termination(&data);
	cleanup_resources(&data, philos, NULL, 0);
	return (0);
}

