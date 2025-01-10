/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:55:30 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/10 15:33:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_starved(t_table *table, int i)
{
	//long	wait;
	if (!get_philo_done(&table->philos[i]))
	{
		//wait = get_time_in_ms() - get_philo_last_meal_time(&table->philos[i]);
		if (get_time_in_ms() - get_philo_last_meal_time(&table->philos[i]) >= table->time_to_die)
		{
			announce(table, table->philos[i].id, "died");
			set_simulation_running(table, 0);
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
		if (!get_philo_done(&table->philos[i]))
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
	while (get_simulation_running(table))
	{
		i = 0;
		while (i < table->num_philos && get_simulation_running(table))
		{
			if (philo_starved(table, i))
				break ;
			i++;
		}
		if (table->must_eat)
		{
			if (is_everyone_full(table))
			{
				set_simulation_running(table, 0);
				break ;
			}
		}
		ft_usleep(1);
	}
	return (NULL);
}
