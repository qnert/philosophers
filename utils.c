/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:04:00 by skunert           #+#    #+#             */
/*   Updated: 2023/06/18 17:27:02 by skunert          ###   ########.fr       */
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
	ft_printf("Hello from Philo %d\n", *(int *)arg);
	return (NULL);
}

t_dinnertable	*dinnertable_init(char **argv)
{
	int				i;
	t_dinnertable	*table;

	i = 1;
	table = malloc(sizeof(t_dinnertable));
	table->nb_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_die = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		table->nb_must_eat = ft_atoi(argv[5]);
	else
		table->nb_must_eat = 0;
	while (i < table->nb_of_philos + 1)
	{
		pthread_create(&table->philos[i - 1], NULL, &routine, (void *)&i);
		pthread_mutex_init(&table->forks[i - 1], NULL);
		pthread_join(table->philos[i - 1], NULL);
		i++;
	}
	return (table);
}
