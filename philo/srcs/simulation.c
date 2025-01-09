/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:17:12 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/06 15:58:06 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_table *table, int count)
{
	int	i;
	int	error_join;

	i = 0;
	error_join = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			error_join = 1;
		i++;
	}
	if (error_join)
		return (0);
	return (1);
}

int	destroy_meal_locks(t_table *table, int count)
{
	int	i;
	int	error_join;

	i = 0;
	error_join = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&table->philos[i].meal_lock) != 0)
			error_join = 1;
		i++;
	}
	if (error_join)
		return (0);
	return (1);
}

int	join_threads(t_table *table, int count)
{
	int	i;
	int	error_join;

	i = 0;
	error_join = 0;
	while (i < count)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			error_join = 1;
		i++;
	}
	if (error_join)
		return (0);
	return (1);
}

void	destroy_resources(t_table *table)
{
	destroy_forks(table, table->num_philos);
	destroy_meal_locks(table, table->num_philos);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->sim_lock);
	free(table->forks);
	free(table->philos);
}

int	create_philo_threads(t_table *table)
{
	int		i;
	t_philo	*philo;
	void	*arg;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		arg = (void *)philo;
		philo->last_meal_time = table->start_time;
		if (pthread_create(&philo->thread, NULL, &philo_routine, arg) != 0)
		{
			join_threads(table, i);
			destroy_resources(table);
			return (0);
		}
		i++;
	}
	return (1);
}
