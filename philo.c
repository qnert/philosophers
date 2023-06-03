/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/03 17:04:39 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int	*nb;

	nb = (int *)arg;
	ft_printf("Philosopher %d from process: %d\n", *nb, getpid());
	return (NULL);
}

int	main(void)
{
	pthread_t	philo[3];
	int			i;
	pid_t		pid;

	pid = fork();
	i = 0;
	printf("%d\n", pid);
	while (i < 2)
	{
		pthread_create(&philo[i], NULL, routine, (void *)&i);
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}
