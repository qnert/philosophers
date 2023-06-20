/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:39 by skunert           #+#    #+#             */
/*   Updated: 2023/06/20 10:39:43 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	first_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinnertable->forks[philo->id]);
	pthread_mutex_lock(&philo->dinnertable->forks[(philo->id + 1)
		% philo->dinnertable->nb_of_philos]);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	ft_printf("%d %d has taken a fork\n",
		get_time(philo->dinnertable->birth), philo->id);
	ft_printf("%d %d has taken a fork\n",
		get_time(philo->dinnertable->birth), philo->id);
	ft_printf("%d %d is eating\n",
		get_time(philo->dinnertable->birth), philo->id);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	usleep(philo->dinnertable->time_to_eat);
	pthread_mutex_unlock(&philo->dinnertable->forks[philo->id]);
	pthread_mutex_unlock(&philo->dinnertable->forks[(philo->id + 1)
		% philo->dinnertable->nb_of_philos]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	first_routine(philo);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	ft_printf("%d %d is sleeping\n",
		get_time(philo->dinnertable->birth), philo->id);
	usleep(philo->dinnertable->time_to_sleep);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	ft_printf("%d %d is thinking\n",
		get_time(philo->dinnertable->birth), philo->id);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	return (NULL);
}
