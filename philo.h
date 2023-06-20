/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:40:01 by skunert           #+#    #+#             */
/*   Updated: 2023/06/20 10:54:20 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/time.h>

typedef struct Dinnertable
{
	struct timeval	birth;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
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

//input check
int				check_input(char **argv);

//initialization of the structs
void			philo_init(t_philo	**philosophers, char **argv);
t_dinnertable	*dinnertable_init(char **argv);

//timestamp
int				get_time(struct timeval birth);

//thread function
void			*routine(void *arg);

#endif