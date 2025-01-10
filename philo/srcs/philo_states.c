/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:14:26 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/10 16:14:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_table *table, int id, const char *msg)
{
	if (get_simulation_running(table))
	{
		announce(table, id, msg);
	}
}

int	thinking_state(t_table *table, t_philo *philo)
{
	if (!get_simulation_running(table))
		return (0);
	print_state(table, philo->id, "is thinking");
	ft_usleep(1);
	return (1);
}

int	eating_state(t_table *table, t_philo *philo)
{
	if (!get_simulation_running(table))
		return (0);
	pickup_forks(philo);
	philo_eat(philo);
	putdown_forks(philo);
	return (1);
}

int	sleeping_state(t_table *table, t_philo *philo)
{
	if (!get_simulation_running(table))
		return (0);
	print_state(table, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep);
	return (1);
}
