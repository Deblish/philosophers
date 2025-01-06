/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:17:12 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/03 14:58:08 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_resources(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philos);
}

int	start_simulation(t_table *table)
{
	int			i;
	t_philo		*philo;
	pthread_t	monitor_thread;

	table->start_time = ft_get_time_in_ms();

	//create each philosopher thread
	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->last_meal_time = table->start_time; //initialize last_meal_time
		if (pthread_create(&philo->thread, NULL, &philo_routine, (void *)philo) != 0)
			return (0);
		i++;
	}
	//create the monitor thread.
	//which loops until someone dies or must_eat condition is met
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, (void *)table) != 0)
		return (0);
	//join philosopher threads
	//once simulation_running is 0, philosophers loops end and exit
	//we wait for them all
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	//join monitor thread
	//monitor also stops once !simulation_running
	if (pthread_join(monitor_thread, NULL) != 0)
		return (0);
	//destroy all mutexes and free
	destroy_resources(table);

	return (1);
}


