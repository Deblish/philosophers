/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:06:52 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/07 18:18:54 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_state(t_table *table, int id, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&table->print_lock);
	if (table->simulation_running) //still running?
	{
		timestamp = ft_get_time_in_ms() - table->start_time;
		printf("%ld %d %s\n", timestamp, id, msg);
	}
	pthread_mutex_unlock(&table->print_lock);
}

static void	philo_eat(t_philo *philo)
{
	t_table	*table;
	long	now;

	table = philo->table;
	now = ft_get_time_in_ms();
	philo->last_meal_time = now; //just before printing
	print_state(table, philo->id, "is eating");
	ft_usleep(table->time_to_eat); //philosopher eats (holds both forks)
	philo->eat_count += 1;
	if (table->must_eat && philo->eat_count >= table->must_eat_count)
		philo->done = 1;
}

static void	pickup_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philos;
	//prevents deadlock, pick even's right fork first
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

static void	putdown_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philos;
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

void	*single_philo_case(t_table *table, t_philo *philo)
{
	print_state(table, philo->id, "has taken a fork");
	ft_usleep(table->time_to_die);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	//handle: if 0?
	if (table->num_philos == 1)
		return (single_philo_case(table, philo));
	while (table->simulation_running && !philo->done)
	{
		//think
		print_state(table, philo->id, "is thinking");
		ft_usleep(1); //avoid immediate grab fork
		//sim already ended?
		if (!table->simulation_running)
			break ;
		pickup_forks(philo);
		philo_eat(philo);
		putdown_forks(philo);
		//sleep
		print_state(table, philo->id, "is sleeping");
		ft_usleep(table->time_to_sleep);
	}
	return (NULL);
}
