/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/30 16:18:38 by skunert          ###   ########.fr       */
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

	if (argc == 5)
	{
		if (check_input(argv) == 0)
			return (write(1, "Input Error\n", 12), -1);
		philosophers = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
		philo_init(philosophers, argv);
		free_all(philosophers);
	}
	else if (argc == 6)
	{
		if (check_input(argv) == 0)
			return (write(1, "Input Error\n", 12), -1);
		philosophers = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
		philo_init(philosophers, argv);
		free_all(philosophers);
	}
	else
		write(1, "Wrong amount of arguments!\n", 27);
}
