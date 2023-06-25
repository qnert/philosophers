/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:51:08 by skunert           #+#    #+#             */
/*   Updated: 2023/06/25 14:20:29 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_time(struct timeval birth)
{
	unsigned long	milli;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	milli = (curr_time.tv_sec - birth.tv_sec) * 1000
		+ (curr_time.tv_usec - birth.tv_usec) / 1000;
	return (milli);
}
