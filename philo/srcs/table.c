/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:27 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/07 18:18:19 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//allocate and init forks (mutex array)
static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_mutex) * table->num_philos);
	if (!table->forks)
		return (0);
	memset(table->forks, 0, sizeof(t_mutex) * table->num_philos);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_mutexes(table, i);
			free(table->forks);
			table->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

//init print lock (mutex for printing)
static int	init_print_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		destroy_mutexes(table, table->num_philos);
		free(table->forks);
		table->forks = NULL;
		return (0);
	}
	return (1);
}

//allocate and init philosophers (t_philo (thread + info) array)
static int	init_philosophers(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
	{
		destroy_mutexes(table, table->num_philos);
		free(table->forks);
		table->forks = NULL;
		pthread_mutex_destroy(&table->print_lock);
		return (0);
	}
	memset(table->philos, 0, sizeof(t_philo) * table->num_philos);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

int	init_table(t_table *table)
{
	if (!init_forks(table))
		return (0);
	if (!init_print_mutex(table))
		return (0);
	if (!init_philosophers(table))
		return (0);
	table->simulation_running = 1;
	table->start_time = 0;
	return (1);
}
