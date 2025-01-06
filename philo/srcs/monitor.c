/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:55:30 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/03 14:55:32 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	announce_death(t_table *table, int id)
{
	long	timestamp;

	/* It's safer to lock printing */
	pthread_mutex_lock(&table->print_lock);
	timestamp = ft_get_time_in_ms() - table->start_time;
	printf("%ld %d died\n", timestamp, id);
	pthread_mutex_unlock(&table->print_lock);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	now;
	int		done_count;
	//int		eaten_count;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = 0;
		while (i < table->num_philos && table->simulation_running)
		{
			//lock around reading philo->last_meal_time
			now = ft_get_time_in_ms();
			if ((now - table->philos[i].last_meal_time) >= table->time_to_die)
			{
				table->simulation_running = 0;
				announce_death(table, table->philos[i].id);
				break ;
			}
			i++;
		}
		if (table->must_eat)
		{
			/*
			//v1
			eaten_count = 0;
			i = 0;
			while (i < table->num_philos)
			{
				if (table->philos[i].eat_count >= table->must_eat_count)
					eaten_count++;
				i++;
			}
			if (eaten_count == table->num_philos)
			{
				table->simulation_running = 0;
				//break ;
			}
			*/
			//v2
			done_count = 0;
			i = 0;
			while (i < table->num_philos)
			{
				if (table->philos[i].done)
					done_count++;
				i++;
			}
			if (done_count == table->num_philos)
			{
				table->simulation_running = 0;
				//break ;
			}
		}
		usleep(1000); //check every 1ms (small cpu optimization)
	}
	return (NULL);
}
