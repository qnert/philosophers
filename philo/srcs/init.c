/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:05:18 by skunert           #+#    #+#             */
/*   Updated: 2023/07/11 13:45:08 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_protection(t_dinnertable *table, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_destroy(&table->forks[i]);
}

int	mutex_create(t_dinnertable *table)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = table->nb_of_philos;
	if (pthread_mutex_init(&table->printf_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->time_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&table->printf_mutex), -1);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&table->printf_mutex),
			pthread_mutex_destroy(&table->time_mutex), -1);
	while (i < tmp)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (mutex_protection(table, i), 1);
		i++;
	}
	return (1);
}

int	thread_creation(t_philo **philosophers)
{
	int	i;

	i = -1;
	if (mutex_create(philosophers[0]->dinnertable) == -1)
		return (-2);
	if (pthread_create(&philosophers[0]->dinnertable->waiter, NULL,
			&check_death_routine, philosophers) != 0)
		return (-1);
	while (++i < philosophers[0]->dinnertable->nb_of_philos)
	{
		if (pthread_create(&philosophers[i]->thread, NULL,
				&routine, (void *)philosophers[i]) != 0)
			return (-1);
	}
	i = -1;
	if (pthread_join(philosophers[0]->dinnertable->waiter, NULL) != 0)
		return (-1);
	while (++i < philosophers[0]->dinnertable->nb_of_philos)
		if (pthread_join(philosophers[i]->thread, NULL) != 0)
			return (-1);
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
		philosophers[i] = malloc(1 * sizeof(t_philo));
		if (philosophers[i] == NULL)
			return (free_arr(philosophers, i), -1);
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

	table = malloc(1 * sizeof(t_dinnertable));
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
	table->death_occ = 0;
	return (table);
}
