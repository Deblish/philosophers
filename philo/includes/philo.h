/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:44 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/07 18:12:17 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//pthread_t: create, join, detach 
//pthread_mutex_t: init, lock, unlock, destroy
# include <pthread.h> 
# include <stdio.h> //printf 
# include <stdlib.h> //malloc, free
# include <unistd.h> //usleep, write
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX, INT_MIN
# include <string.h> //memset
# include <errno.h> //errno

typedef struct s_table	t_table;

//optional typedefs to make code (a little) more readable
typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				done;
	long			last_meal_time;
	t_mutex			meal_lock;
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
	t_mutex			sim_lock;
	long			start_time;
	t_philo			*philos;
	t_mutex			*forks;
	t_mutex			print_lock;
}	t_table;

//getters.c
void	announce(t_table *table, int id, const char *msg);
int		get_philo_done(t_philo *philo);
int		get_simulation_running(t_table *table);
long	get_philo_last_meal_time(t_philo *philo);

//setters.c
void	set_philo_done(t_philo *philo, int value);
void	set_simulation_running(t_table *table, int running);
void	set_philo_last_meal_time(t_philo *philo, long value);

//table_inits.c
int		init_forks(t_table *table);
int		init_print_lock(t_table *table);
int		init_sim_lock(t_table *table);
int		init_philosophers(t_table *table);
int		init_meal_locks(t_table *table);

//main.c
int		init_table(t_table *table);
int		main(int argc, char **argv);

//parse.c
int		parse_args(int argc, char **argv, t_table *table);

//libft.c
int		ft_str_is_digit(char *str);
int		ft_atoi(const char *str);

//time.c
long	get_time_in_ms(void);
void	ft_usleep(long ms);

//routine.c
void	*philo_routine(void *arg);

//simulation.c
int		destroy_forks(t_table *table, int count);
int		destroy_meal_locks(t_table *table, int count);
int		join_threads(t_table *table, int count);
void	destroy_resources(t_table *table);
int		create_philo_threads(t_table *table);

//monitor.c
void	*monitor_routine(void *arg);

#endif
