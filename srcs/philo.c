/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/19 08:47:56 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_dinnertable *table)
{
	int	i;

	i = 0;
	while (i < table->nb_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table);
}

int	main(int argc, char **argv)
{
	t_dinnertable	*table;

	if (argc == 5)
	{
		if (check_input(argv) == 0)
			return (write(1, "Input Error\n", 12), -1);
		table = dinnertable_init(argv);
		if (table == NULL)
			return (-1);
		free_all(table);
	}
	else if (argc == 6)
	{
		if (check_input(argv) == 0)
			return (write(1, "Input Error\n", 12), -1);
		table = dinnertable_init(argv);
		if (table == NULL)
			return (-1);
		free_all(table);
	}
	else
		write(1, "Wrong amount of arguments!\n", 27);
}
