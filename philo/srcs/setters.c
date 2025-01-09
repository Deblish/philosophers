/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:32 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/09 16:20:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo_done(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->done = value;
	pthread_mutex_unlock(&philo->meal_lock);
}

void	set_simulation_running(t_table *table, int value)
{
	pthread_mutex_lock(&table->sim_lock);
	table->simulation_running = value;
	pthread_mutex_unlock(&table->sim_lock);
}

void	set_philo_last_meal_time(t_philo *philo, long value)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = value;
	pthread_mutex_unlock(&philo->meal_lock);
}
