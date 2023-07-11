/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:39 by skunert           #+#    #+#             */
/*   Updated: 2023/07/11 11:42:47 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	first_routine(t_philo *philo)
{
	if (safe_fork_take(philo) == -1)
		return (printf_safe("has taken a fork", philo,
				get_time(philo->dinnertable->birth)), -1);
	printf_safe("has taken a fork", philo, get_time(philo->dinnertable->birth));
	printf_safe("has taken a fork", philo, get_time(philo->dinnertable->birth));
	printf_safe("is eating", philo, get_time(philo->dinnertable->birth));
	philo->times_eaten += 1;
	philo->time_since_eaten = get_time(philo->dinnertable->birth);
	usleep_ms(philo->dinnertable->time_to_eat);
	safe_release(philo);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (first_routine(philo) == -1)
			break ;
		if (philo->times_eaten == philo->dinnertable->nb_must_eat)
			break ;
		pthread_mutex_lock(&philo->dinnertable->death_mutex);
		if (philo->dinnertable->death_occ == 1)
		{
			pthread_mutex_unlock(&philo->dinnertable->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->dinnertable->death_mutex);
		printf_safe("is sleeping", philo, get_time(philo->dinnertable->birth));
		usleep_ms(philo->dinnertable->time_to_sleep);
		printf_safe("is thinking", philo, get_time(philo->dinnertable->birth));
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
			printf_safe("died", philos[i],
				get_time(philos[i]->dinnertable->birth));
			pthread_mutex_lock(&philos[i]->dinnertable->death_mutex);
			philos[i]->dinnertable->death_occ = 1;
			pthread_mutex_unlock(&philos[i]->dinnertable->death_mutex);
			break ;
		}
		i++;
	}
	return (NULL);
}
