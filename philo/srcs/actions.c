/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:34:19 by skunert           #+#    #+#             */
/*   Updated: 2023/07/11 11:42:10 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	safe_release(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->dinnertable->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->dinnertable->forks[philo->id
			% philo->dinnertable->nb_of_philos]);
	}
	else
	{
		pthread_mutex_unlock(&philo->dinnertable->forks[philo->id
			% philo->dinnertable->nb_of_philos]);
		pthread_mutex_unlock(&philo->dinnertable->forks[philo->id - 1]);
	}
}

int	safe_fork_take(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->dinnertable->forks[philo->id - 1]);
		if (philo->dinnertable->nb_of_philos == 1)
			return (pthread_mutex_unlock(&philo->dinnertable->forks
					[philo->id - 1]), -1);
		pthread_mutex_lock(&philo->dinnertable->forks[philo->id
			% philo->dinnertable->nb_of_philos]);
	}
	else
	{
		pthread_mutex_lock(&philo->dinnertable->forks[philo->id
			% philo->dinnertable->nb_of_philos]);
		pthread_mutex_lock(&philo->dinnertable->forks[philo->id - 1]);
	}
	return (0);
}

void	printf_safe(char *msg, t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->dinnertable->death_mutex);
	if (philo->dinnertable->death_occ == 0)
	{
		pthread_mutex_lock(&philo->dinnertable->printf_mutex);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	}
	pthread_mutex_unlock(&philo->dinnertable->death_mutex);
}
