/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:56:14 by met-tahe          #+#    #+#             */
/*   Updated: 2023/02/13 21:56:16 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			res;

	gettimeofday(&tv, NULL);
	res = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);
	return (res);
}

time_t	time_delai(struct timeval delai, struct timeval start)
{
	time_t	d;
	time_t	s;
	time_t	res;

	s = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	d = (delai.tv_sec * 1000) + (delai.tv_usec / 1000);
	res = d - s;
	return (res);
}

void	timer(time_t time)
{
	struct timeval	start;
	struct timeval	delai;

	gettimeofday(&start, NULL);
	gettimeofday(&delai, NULL);
	while (1)
	{
		gettimeofday(&delai, NULL);
		if (time_delai(delai, start) >= time)
			break ;
		usleep(150);
	}
}
