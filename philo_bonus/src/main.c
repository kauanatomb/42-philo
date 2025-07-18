/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:12:52 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (parse_args(argc, argv, &data))
		return (exit_error("Invalid arguments."));
	if (init_semaphores(&data))
	{
		cleanup_semaphores(&data);
		return (exit_error("Failed to init semaphores"));
	}
    if (init_allocs(&data, &philos))
	{
		cleanup_resources(&data, philos);
		return (exit_error("Malloc failed"));
	}
	if (start_processes(&data) != 0)
	{
		kill_all_processes(&data);
		cleanup_resources(&data, philos);
		return (exit_error("Failed to fork"));
	}
	wait_for_termination(&data);
	cleanup_resources(&data, philos);
	return (0);
}
