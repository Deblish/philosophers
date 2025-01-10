/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:16:07 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/10 15:30:49 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	announce(t_table *table, int id, const char *msg)
{
	//long	timestamp;

	//timestamp = get_time_in_ms() - table->start_time;
	pthread_mutex_lock(&table->print_lock);
	if (get_simulation_running(table))
		printf("%ld %d %s\n", get_time_in_ms() - table->start_time, id, msg);
	pthread_mutex_unlock(&table->print_lock);
}

int	get_philo_done(t_philo *philo)
{
	int	done;

	pthread_mutex_lock(&philo->meal_lock);
	done = philo->done;
	pthread_mutex_unlock(&philo->meal_lock);
	return (done);
}

int	get_simulation_running(t_table *table)
{
	int	running;

	pthread_mutex_lock(&table->sim_lock);
	running = table->simulation_running;
	pthread_mutex_unlock(&table->sim_lock);
	return (running);
}

long	get_philo_last_meal_time(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (last_meal_time);
}
