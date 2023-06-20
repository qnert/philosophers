/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:12:12 by skunert           #+#    #+#             */
/*   Updated: 2023/06/20 17:45:51 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_times_eaten(t_philo *philo)
{
	if (philo->dinnertable->nb_must_eat == 0)
		return (1);
	if (philo->dinnertable->nb_must_eat == philo->times_eaten)
		return (0);
	return (1);
}

int	check_nbs(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			check = 1;
		if (str[i] < '0' || str[i] > '9')
			if ((str[i] == '+' && check == 1) || str[i] != '+')
				return (0);
		i++;
	}
	if (ft_atoi(str) == 0)
		return (0);
	return (1);
}

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (check_nbs(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
