/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:55:30 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/06 15:59:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	announce_death(t_table *table, int id)
{
	long	timestamp;

	pthread_mutex_lock(&table->print_lock);
	timestamp = ft_get_time_in_ms() - table->start_time;
	printf("%ld %d died\n", timestamp, id);
	pthread_mutex_unlock(&table->print_lock);
}

static int	philo_starved(t_table *table, int i)
{
	long	waited;

	if (!table->philos[i].done)
	{
		//lock around reading philo->last_meal_time
		waited = ft_get_time_in_ms() - table->philos[i].last_meal_time;
		if (waited >= table->time_to_die)
		{
			table->simulation_running = 0;
			announce_death(table, table->philos[i].id);
			return (1);
		}
	}
	return (0);
}

static int	is_everyone_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (!table->philos[i].done)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = 0;
		while (i < table->num_philos && table->simulation_running)
		{
			if (philo_starved(table, i))
				break ;
			i++;
		}
		if (table->must_eat)
		{
			if (is_everyone_full(table))
			{
				table->simulation_running = 0;
				break ;
			}
		}
		ft_usleep(1); //(small cpu optimization)
	}
	return (NULL);
}
