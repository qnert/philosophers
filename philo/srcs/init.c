/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:05:18 by skunert           #+#    #+#             */
/*   Updated: 2023/07/01 10:10:13 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	mutex_create(t_dinnertable *table)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = table->nb_of_philos;
	while (i < tmp)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->printf_mutex, NULL);
	return (1);
}

int	thread_creation(t_philo **philosophers)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = philosophers[0]->dinnertable->nb_of_philos;
	mutex_create(philosophers[0]->dinnertable);
	if (pthread_create(&philosophers[0]->dinnertable->waiter, NULL,
			&check_death_routine, philosophers) != 0)
		return (-1);
	while (++i < tmp)
	{
		if (pthread_create(&philosophers[i]->thread, NULL,
				&routine, (void *)philosophers[i]) != 0)
			return (-1);
		usleep(50);
	}
	i = -1;
	if (pthread_join(philosophers[0]->dinnertable->waiter, NULL) != 0)
		return (-1);
	while (++i < tmp)
	{
		if (pthread_join(philosophers[i]->thread, NULL) != 0)
			return (-1);
	}
	return (1);
}

int	philo_init(t_philo	**philosophers, char **argv)
{
	int				i;
	t_dinnertable	*table;

	i = 0;
	table = dinnertable_init(argv);
	if (table == NULL)
		return (-1);
	while (i < table->nb_of_philos)
	{
		philosophers[i] = ft_calloc(1, sizeof(t_philo));
		if (philosophers[i] == NULL)
			return (free_arr(philosophers), -1);
		philosophers[i]->id = i + 1;
		philosophers[i]->time_since_eaten = 0;
		philosophers[i]->times_eaten = 0;
		philosophers[i]->dinnertable = table;
		i++;
	}
	thread_creation(philosophers);
	return (1);
}

t_dinnertable	*dinnertable_init(char **argv)
{
	t_dinnertable	*table;

	table = ft_calloc(1, sizeof(t_dinnertable));
	if (table == NULL)
		return (NULL);
	gettimeofday(&table->birth, NULL);
	table->nb_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		table->nb_must_eat = ft_atoi(argv[5]);
	else
		table->nb_must_eat = 0;
	return (table);
}
