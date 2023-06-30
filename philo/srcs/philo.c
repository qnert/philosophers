/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/30 18:53:20 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	kill_all(t_philo **philosophers)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = philosophers[0]->dinnertable->nb_of_philos;
	while (i < tmp)
	{
		pthread_detach(philosophers[i]->thread);
		i++;
	}
}

void	free_arr(t_philo **philos)
{
	unsigned int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	free_all(t_philo **philosophers)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = philosophers[0]->dinnertable->nb_of_philos;
	while (i < tmp)
	{
		pthread_mutex_destroy(&philosophers[0]->dinnertable->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosophers[0]->dinnertable->printf_mutex);
	free(philosophers[0]->dinnertable);
	while (i < tmp)
	{
		free(philosophers[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			**philosophers;

	if (argc == 5 || argc == 6)
	{
		if (check_input(argv) == 0)
			return (write(1, "Input Error\n", 12), -1);
		philosophers = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
		if (philosophers == NULL)
			return (-1);
		philo_init(philosophers, argv);
		free_all(philosophers);
		free(philosophers);
	}
	else
		write(1, "Wrong amount of arguments!\n", 27);
	return (0);
}
