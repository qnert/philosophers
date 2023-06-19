/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:51:08 by skunert           #+#    #+#             */
/*   Updated: 2023/06/19 14:09:54 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

struct timeval	get_time(struct timeval birth)
{
	struct timeval	curr_time;
	struct timeval	timestamp;

	gettimeofday(&curr_time, NULL);
	timestamp.tv_usec = (curr_time.tv_usec - birth.tv_usec) + (curr_time.tv_usec % birth.tv_sec) / 1000;
	return (timestamp);
}