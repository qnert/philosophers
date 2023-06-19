/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:04:00 by skunert           #+#    #+#             */
/*   Updated: 2023/06/19 07:08:15 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*routine(void *arg)
{
	t_dinnertable	*table;

	table = (t_dinnertable *)arg;
	ft_printf("Hello from Philo %d\n", table->tmp + 1);
	return (NULL);
}

t_dinnertable	*dinnertable_init(char **argv)
{
	int				i;
	t_dinnertable	*table;

	i = 0;
	table = malloc(sizeof(t_dinnertable));
	table->nb_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		table->nb_must_eat = ft_atoi(argv[5]);
	else
		table->nb_must_eat = 0;
	while (i < table->nb_of_philos)
	{
		table->tmp = i;
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_create(&table->philos[i], NULL, &routine, (void *)table);
		pthread_join(table->philos[i], NULL);
		i++;
	}
	return (table);
}
