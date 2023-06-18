/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:04:00 by skunert           #+#    #+#             */
/*   Updated: 2023/06/18 16:20:16 by skunert          ###   ########.fr       */
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
	int				tmp;
	t_dinnertable	*table;

	i = 0;
	tmp = ft_atoi(argv[1]);
	table = malloc(sizeof(t_dinnertable));
	while (i < tmp)
	{
		pthread_create(&table->philos[i], NULL, &routine, (void *)&i);
		pthread_join(table->philos[i], NULL);
		i++;
	}
	return (table);
}
