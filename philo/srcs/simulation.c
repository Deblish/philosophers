/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:17:12 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/06 15:58:06 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

int	join_threads(t_table *table, int count)
{
	int	i;
	int	error_join;

	i = 0;
	error_join = 0;
	while (i < count)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			error_join = 1;
		i++;
	}
	if (error_join)
		return (0);
	return (1);
}

void	destroy_resources(t_table *table)
{
	destroy_mutexes(table, table->num_philos);
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philos);
}

static int	create_philo_threads(t_table *table)
{
	int		i;
	t_philo	*philo;
	void	*arg;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		arg = (void *)philo;
		philo->last_meal_time = table->start_time;
		if (pthread_create(&philo->thread, NULL, &philo_routine, arg) != 0)
		{
			join_threads(table, i);
			destroy_resources(table);
			return (0);
		}
		i++;
	}
	return (1);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;
	void		*arg;

	table->start_time = ft_get_time_in_ms();
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
