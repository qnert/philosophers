/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:39 by skunert           #+#    #+#             */
/*   Updated: 2023/06/26 14:20:29 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	first_routine(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->dinnertable->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->dinnertable->forks[(philo->id)
		% philo->dinnertable->nb_of_philos]);
	pthread_mutex_lock(&philo->dinnertable->printf_mutex);
	time = get_time(philo->dinnertable->birth);
	ft_printf("%d %d has taken a fork\n",
		time, philo->id);
	ft_printf("%d %d has taken a fork\n",
		time, philo->id);
	ft_printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	philo->times_eaten += 1;
	usleep_ms(philo->dinnertable->time_to_eat);
	pthread_mutex_unlock(&philo->dinnertable->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->dinnertable->forks[(philo->id)
		% philo->dinnertable->nb_of_philos]);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (check_times_eaten(philo) == 1)
	{
		first_routine(philo);
		if (check_times_eaten(philo) == 0)
			break ;
		pthread_mutex_lock(&philo->dinnertable->printf_mutex);
		ft_printf("%d %d is sleeping\n",
			get_time(philo->dinnertable->birth), philo->id);
		pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
		usleep_ms(philo->dinnertable->time_to_sleep);
		pthread_mutex_lock(&philo->dinnertable->printf_mutex);
		ft_printf("%d %d is thinking\n",
			get_time(philo->dinnertable->birth), philo->id);
		pthread_mutex_unlock(&philo->dinnertable->printf_mutex);
	}
	return (NULL);
}
