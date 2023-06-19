/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:04:00 by skunert           #+#    #+#             */
/*   Updated: 2023/06/19 15:03:02 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	thread_creation(t_philo **philosophers)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = philosophers[0]->dinnertable->nb_of_philos;
	while (i < tmp)
	{
		pthread_mutex_init(&philosophers[i]->dinnertable->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philosophers[0]->dinnertable->printf_mutex, NULL);
	i = 0;
	while (i < tmp)
	{
		pthread_create(&philosophers[i]->thread, NULL,
			&routine, (void *)philosophers[i]);
		i++;
	}
	i = 0;
	while (i < tmp)
	{
		pthread_join(philosophers[i]->thread, NULL);
		i++;
	}
}

void	philo_init(t_philo	**philosophers, char **argv)
{
	int				i;
	t_dinnertable	*table;

	i = 0;
	table = dinnertable_init(argv);
	while (i < table->nb_of_philos)
	{
		philosophers[i] = ft_calloc(1, sizeof(t_philo));
		philosophers[i]->id = i + 1;
		philosophers[i]->time_since_eaten = 0;
		philosophers[i]->times_eaten = 0;
		philosophers[i]->dinnertable = table;
		i++;
	}
	thread_creation(philosophers);
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
