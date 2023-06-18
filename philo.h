/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:40:01 by skunert           #+#    #+#             */
/*   Updated: 2023/06/18 16:19:20 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

typedef struct Dinnertable
{
	int				tmp;
	pthread_mutex_t	*forks;
	pthread_t		philos[];
}					t_dinnertable;

int				check_input(char **argv);
t_dinnertable	*dinnertable_init(char **argv);

#endif