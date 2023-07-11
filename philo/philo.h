/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:40:01 by skunert           #+#    #+#             */
/*   Updated: 2023/07/11 11:37:45 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/time.h>

typedef struct Dinnertable
{
	struct timeval	birth;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				death_occ;
	pthread_t		waiter;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	forks[200];
}					t_dinnertable;

typedef struct Philo
{
	int				id;
	int				time_since_eaten;
	int				times_eaten;
	pthread_t		thread;
	t_dinnertable	*dinnertable;
}					t_philo;

//utils
void			ft_bzero(void *dst, size_t n);
void			*ft_calloc(size_t nitems, size_t size);
int				ft_atoi(const char *str);
void			kill_all(t_philo **philosophers);
void			free_arr(t_philo **philos, int size);
long			ft_atol(const char *str);
size_t			ft_strlen(const char *str);

//check funcs
int				check_input(char **argv);
int				check_times_eaten(t_philo *philo);

//initialization of the structs
int				philo_init(t_philo	**philosophers, char **argv);
t_dinnertable	*dinnertable_init(char **argv);

//timestamp
long			get_time(struct timeval birth);
void			usleep_ms(int ms);

//thread function
void			*routine(void *arg);
void			*check_death_routine(void *arg);

//actions
void			safe_release(t_philo *philo);
int				safe_fork_take(t_philo *philo);
void			printf_safe(char *msg, t_philo *philo, long time);

#endif
