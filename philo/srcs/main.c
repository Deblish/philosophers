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

//./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]
int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (!parse_args(argc, argv, &table))
	{
		printf("Error: invalid arguments\n");
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
	//cleanup //all full or someone died, rip
	return (0);
}
