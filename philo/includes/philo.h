/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:44 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/03 17:33:24 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> //pthread_t: create, join, detach //pthread_mutex_t: init, lock, unlock, destroy
# include <stdio.h> //printf 
# include <stdlib.h> //malloc, free
# include <unistd.h> //usleep, write
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX, INT_MIN
# include <string.h> //memset

typedef struct s_table t_table;

//optional typedefs to make code (a little) more readable
typedef pthread_t t_thread;
typedef pthread_mutex_t t_mutex;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				done;
	long			last_meal_time;
	t_thread		thread;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				must_eat_count;

	int				simulation_running;
	long			start_time;
	t_philo			*philos;
	t_mutex			*forks;
	t_mutex			print_lock;
}	t_table;

//main.c
int		main(int argc, char **argv);

//parse.c
int		parse_args(int argc, char **argv, t_table *table);

//init.c
int		init_table(t_table *table);

//libft.c
int		ft_strlen(const char *str);
int		ft_str_is_digit(char *str);
int		ft_atoi(const char *str);

//time.c
long	ft_get_time_in_ms(void);
void	ft_usleep(long ms);

//routine.c
void	*philo_routine(void *arg);

//simulation.c
int		start_simulation(t_table *table);

//monitor.c
void	*monitor_routine(void *arg);

#endif
