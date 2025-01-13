/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:08:13 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/13 11:08:15 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cycle_think_first(t_table *table, t_philo *philo)
{
	if (!thinking_state(table, philo))
		return (0);
	if (!eating_state(table, philo))
		return (0);
	if (!sleeping_state(table, philo))
		return (0);
	return (1);
}

int	cycle_eat_first(t_table *table, t_philo *philo)
{
	if (!eating_state(table, philo))
		return (0);
	if (!sleeping_state(table, philo))
		return (0);
	if (!thinking_state(table, philo))
		return (0);
	return (1);
}
