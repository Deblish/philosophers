/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:13:43 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/06 15:54:02 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_single_arg(char *arg, long *dst)
{
	int		number;

	if (!ft_str_is_digit(arg))
		return (0);
	number = ft_atoi(arg);
	if (number <= 0) //time, counts, etc, must be > 0
		return (0);
	*dst = number; //implicit cast to long
	return (1);
}

//./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]
int	parse_args(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (!parse_single_arg(argv[1], (long *)&table->num_philos))
		return (0);
	if (!parse_single_arg(argv[2], &table->time_to_die))
		return (0);
	if (!parse_single_arg(argv[3], &table->time_to_eat))
		return (0);
	if (!parse_single_arg(argv[4], &table->time_to_sleep))
		return (0);
	table->must_eat = 0;
	if (argc == 6)
	{
		if (!parse_single_arg(argv[5], (long *)&table->must_eat_count))
			return (0);
		table->must_eat = 1;
	}
	if (table->num_philos < 1 || table->num_philos > 200)
		return (0);
	return (1);
}
