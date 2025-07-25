/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:05:42 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int check_death(t_philo *philo)
{
    long current_time;
    
    sem_wait(philo->data->death);
    current_time = get_time_ms();
    if (current_time - philo->last_meal_time > philo->data->time_to_die)
    {
        print_action(philo, "died");
        sem_post(philo->data->death);
        exit(1);
    }
    sem_post(philo->data->death);
    return (0);
}

static int check_meals(t_philo *philo)
{
    static int already_signaled = 0;
    
    if (philo->data->must_eat_count <= 0)
        return (0);
        
    sem_wait(philo->data->death);
    int current_meals = philo->n_meals;
    sem_post(philo->data->death);
    
    if (current_meals >= philo->data->must_eat_count && !already_signaled)
    {
        printf("DEBUG: Philosopher %d completed %d meals\n", 
               philo->id + 1, current_meals);
        already_signaled = 1;
        sem_post(philo->data->meal);
        
        // NÃO fazer exit! Continuar no loop infinito
        while (1)
            safe_usleep(100);  // Espera ser morto pelo processo pai
    }
    return (0);
}

void *ft_monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        safe_usleep(1);
        if (check_death(philo))
            return (NULL);
		check_meals(philo);
    }
    return (NULL);
}
