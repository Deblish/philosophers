/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:27 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/06 15:57:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table)
{
	int	i;

	//allocate forks (mutex array)
	table->forks = malloc(sizeof(t_mutex) * table->num_philos);
	if (!table->forks)
		return (0);
	//remove when gc_alloc is implemented
	memset(table->forks, 0, sizeof(t_mutex) * table->num_philos);
	//init fork
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	//init print lock (mutex for printing)
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	//allocate philosophers (t_philo (thread + info) array)
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		//free forks
		return (0);
	//just because i havent implemented gc_alloc yet
	memset(table->philos, 0, sizeof(t_philo) * table->num_philos);
	//init philosopher info
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1; //numbered 1..n
		table->philos[i].eat_count = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].done = 0;
		table->philos[i].table = table;
		//thread init done in start_simulation
		i++;
	}
	table->simulation_running = 1; //table exists, so true
	table->start_time = 0; //simulation start time goes here
	return (1);
}
