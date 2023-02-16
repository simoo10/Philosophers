/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:58:13 by met-tahe          #+#    #+#             */
/*   Updated: 2023/02/13 11:58:15 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_input *arg)
{
	int	i;

	i = -1;
	arg->philos = malloc(sizeof(t_philo) * arg->nb_philo);
	if (!arg->philos)
		return (1);
	if (pthread_mutex_init(&arg->count, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&arg->eat, NULL) != 0)
		return (1);
	while (++i < arg->nb_philo)
	{
		if (pthread_mutex_init(&arg->philos[i].fork, NULL) != 0)
			return (1);
	}
	return (0);
}

int	init_thread(t_philo *th, t_input *arg)
{
	int	i;

	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_create(&th[i].ph, NULL, routine, &th[i]) != 0)
			return (1);
		pthread_detach(th[i].ph);
	}
	return (0);
}

void	last_philo(t_input *arg, int i)
{
	arg->philos[i].right_philo = &arg->philos[0];
	arg->philos[i].rfork = 0;
}

int	init_philo(t_input *arg)
{
	int	i;

	i = -1;
	while (++i < arg->nb_philo)
	{
		arg->philos[i].philo_id = i + 1;
		arg->philos[i].lfork = i;
		arg->philos[i].last_meal = 0;
		arg->philos[i].m_eat = arg->m_eat;
		arg->philos[i].m_count = 0;
		arg->philos[i].start = arg->start;
		arg->philos[i].args = arg;
		arg->philos[i].eat_time = arg->eat_time;
		arg->philos[i].time_sleep = arg->sleep_time;
		if (i == arg->nb_philo - 1)
			last_philo(arg, i);
		else
		{
			arg->philos[i].right_philo = &arg->philos[i + 1];
			arg->philos[i].rfork = i + 1;
		}
	}
	return (0);
}
