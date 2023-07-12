/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:34:19 by skunert           #+#    #+#             */
/*   Updated: 2023/07/12 12:28:51 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handle_death(t_philo *philo)
{
	printf_safe("died", philo,
		get_time(philo->dinnertable->birth));
	pthread_mutex_lock(&philo->dinnertable->death_mutex);
		philo->dinnertable->death_occ = 1;
	pthread_mutex_unlock(&philo->dinnertable->death_mutex);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinnertable->time_mutex);
	if (get_time(philo->dinnertable->birth)
		- philo->time_since_eaten > philo->dinnertable->time_to_die)
	{
		pthread_mutex_unlock(&philo->dinnertable->time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->dinnertable->time_mutex);
	return (0);
}

void	safe_release(t_philo *philo)
{
	if (philo->id % 2 != 0)
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
	if (philo->id % 2 != 0)
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
