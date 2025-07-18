/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:21:12 by ktombola          #+#    #+#             */
/*   Updated: 2025/07/15 15:00:51 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_safe(const char *str, int *out)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		num = num * 10 + (str[i++] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num) < INT_MIN))
			return (1);
	}
	*out = (int)(num * sign);
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi_safe(argv[1], &data->n_philo)
		|| ft_atoi_safe(argv[2], &data->time_to_die)
		|| ft_atoi_safe(argv[3], &data->time_to_eat)
		|| ft_atoi_safe(argv[4], &data->time_to_sleep))
		return (1);
	if (argc == 6)
	{
		if (ft_atoi_safe(argv[5], &data->must_eat_count)
			|| data->must_eat_count < 1)
			return (1);
	}
	else
		data->must_eat_count = -1;
	if (data->n_philo < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	data->stop = 0;
	return (0);
}
