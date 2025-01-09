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

int	init_table(t_table *table)
{
	if (!init_forks(table))
		return (0);
	if (!init_print_lock(table))
		return (0);
	if (!init_sim_lock(table))
		return (0);
	if (!init_philosophers(table))
		return (0);
	if (!init_meal_locks(table))
		return (0);
	table->simulation_running = 1;
	table->start_time = 0;
	return (1);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;
	void		*arg;

	table->start_time = get_time_in_ms();
	arg = (void *)table;
	if (!create_philo_threads(table))
		return (0);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, arg) != 0)
	{
		join_threads(table, table->num_philos);
		destroy_resources(table);
		return (0);
	}
	if (!join_threads(table, table->num_philos))
	{
		destroy_resources(table);
		return (0);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		destroy_resources(table);
		return (0);
	}
	destroy_resources(table);
	return (1);
}

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
