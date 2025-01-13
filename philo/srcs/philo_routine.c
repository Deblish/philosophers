/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:06:52 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/13 14:24:02 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	set_philo_last_meal_time(philo, get_time_in_ms());
	print_state(table, philo->id, "is eating");
	ft_usleep(table->time_to_eat, table);
	philo->eat_count += 1;
	if (table->must_eat && philo->eat_count >= table->must_eat_count)
	{
		set_philo_done(philo, 1);
	}
}

void	pickup_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[right]);
		print_state(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[left]);
		print_state(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[left]);
		print_state(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[right]);
		print_state(philo->table, philo->id, "has taken a fork");
	}
}

void	putdown_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philos;
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->num_philos == 1)
	{
		print_state(table, philo->id, "has taken a fork");
		ft_usleep(table->time_to_die, table);
		return (NULL);
	}
	set_philo_done(philo, 0);
	if (philo->id % 2 != 0)
	{
		while (get_simulation_running(table) && !get_philo_done(philo))
			if (!cycle_think_first(table, philo))
				break ;
	}
	else
	{
		while (get_simulation_running(table) && !get_philo_done(philo))
			if (!cycle_eat_first(table, philo))
				break ;
	}
	return (NULL);
}
