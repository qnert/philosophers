/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:51:08 by skunert           #+#    #+#             */
/*   Updated: 2023/06/26 14:01:32 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(struct timeval birth)
{
	unsigned long	milli;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	milli = (curr_time.tv_sec - birth.tv_sec) * 1000
		+ (curr_time.tv_usec - birth.tv_usec) / 1000;
	return (milli);
}

void	usleep_ms(int ms)
{
	long			curr_time;
	struct timeval	zero_time;

	zero_time.tv_sec = 0;
	zero_time.tv_usec = 0;
	curr_time = get_time(zero_time);
	while ((get_time(zero_time) - curr_time) < ms)
		usleep(500);
}
