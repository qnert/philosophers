/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:39 by skunert           #+#    #+#             */
/*   Updated: 2023/07/04 10:56:57 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	first_routine(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->dinnertable->forks[philo->id - 1]);
	time = get_time(philo->dinnertable->birth);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	printf("%d %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	pthread_mutex_lock(&philo->dinnertable->forks[(philo->id)
		% philo->dinnertable->nb_of_philos]);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	printf("%d %d has taken a fork\n", time, philo->id);
	printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	philo->times_eaten += 1;
	philo->time_since_eaten = time;
	usleep_ms(philo->dinnertable->time_to_eat);
	pthread_mutex_unlock(&philo->dinnertable->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->dinnertable->forks[(philo->id)
		% philo->dinnertable->nb_of_philos]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		first_routine(philo);
		if (philo->times_eaten == philo->dinnertable->nb_must_eat)
			break ;
		pthread_mutex_lock(&philo->dinnertable->printf_mutex);
		printf("%lu %d is sleeping\n",
			get_time(philo->dinnertable->birth), philo->id);
		pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
		usleep_ms(philo->dinnertable->time_to_sleep);
		pthread_mutex_lock(&philo->dinnertable->printf_mutex);
		printf("%lu %d is thinking\n",
			get_time(philo->dinnertable->birth), philo->id);
		pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	}
	return (NULL);
}

void	*check_death_routine(void *arg)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = (t_philo **)arg;
	while (1)
	{
		if (i == philos[0]->dinnertable->nb_of_philos)
			i = 0;
		if (philos[i]->times_eaten == philos[i]->dinnertable->nb_must_eat
			&& philos[i]->times_eaten != 0)
			break ;
		if (get_time(philos[i]->dinnertable->birth)
			- philos[i]->time_since_eaten > philos[i]->dinnertable->time_to_die)
		{
			pthread_mutex_lock(&philos[i]->dinnertable->printf_mutex);
			printf("%lu %d died\n",
				get_time(philos[i]->dinnertable->birth), philos[i]->id);
			pthread_mutex_unlock(&philos[i]->dinnertable->printf_mutex);
			kill_all(philos);
			break ;
		}
		i++;
	}
	return (NULL);
}
