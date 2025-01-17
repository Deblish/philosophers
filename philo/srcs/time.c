/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:01:51 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/10 15:20:55 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	t;
	long			ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long ms, t_table *table)
{
	long	start;

	start = get_time_in_ms();
	while (get_simulation_running(table) && ((get_time_in_ms() - start) < ms))
		usleep(1000);
}
