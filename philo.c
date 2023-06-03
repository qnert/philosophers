/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/03 16:53:26 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t LOCK;

void	*routine(void *arg)
{
	int	nb;

	nb = *(int *) arg;
	if (nb > -1)
	ft_printf("%d\n", getpid());
	return (NULL);
}
int	main(void)
{
	pthread_t	philo[3];
	int			i;
	pid_t		pid;

	pid = fork();
	i = 0;
	if (pid == 0)
	{
		printf("LOL\n");
	}
	while (i < 2)
	{
		pthread_create(&philo[i], NULL, routine, (void *)&i);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(philo[i], NULL);
		pthread_detach(philo[i]);
		i++;
	}
	return (0);
}
