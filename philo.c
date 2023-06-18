/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:39:33 by skunert           #+#    #+#             */
/*   Updated: 2023/06/18 16:49:46 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dinnertable	*table;

	if (argc == 5)
	{
		if (check_input(argv) == 0)
			write(1, "Input Error\n", 12);
		table = dinnertable_init(argv);
	}
	else if (argc == 6)
	{
		if (check_input(argv) == 0)
			write(1, "Input Error\n", 12);
		table = dinnertable_init(argv);
	}
	else
		write(1, "Wrong amount of arguments!\n", 27);
}
