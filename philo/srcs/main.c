/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:51:04 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/03 14:57:12 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (!parse_args(argc, argv, &table))
	{
		printf("Usage: ./philo t_to_die t_to_eat t_to_sleep [must_eat_n]\n");
		return (1);
	}
	if (!init_table(&table))
	{
		printf("Error: Initializing table failed\n");
		return (2);
	}
	if (!start_simulation(&table))
	{
		printf("Error: Simulation start failed\n");
		return (3);
	}
	return (0);
}
