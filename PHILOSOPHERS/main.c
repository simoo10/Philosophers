/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:58:20 by met-tahe          #+#    #+#             */
/*   Updated: 2023/02/13 11:58:23 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **v)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (v[i])
	{
		j = 0;
		while (v[i][j])
		{
			if (v[i][0] == '+')
				j++;
			if (v[i][j] < 48 || v[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_input	take_input(int c, char **v)
{
	t_input	arg;

	arg.nb_philo = ft_atoi(v[1]);
	arg.death_time = ft_atoi(v[2]);
	arg.eat_time = ft_atoi(v[3]);
	arg.sleep_time = ft_atoi(v[4]);
	if (c == 6)
		arg.m_eat = ft_atoi(v[5]);
	else
		arg.m_eat = -5;
	arg.start = get_time();
	arg.died = 0;
	return (arg);
}

int	main(int c, char **v)
{
	t_input	arg;

	if (check_arg(v) == 1 || (c < 5 || c > 6))
		return (write(1, "INVALID ARGUMENTS\n", 18), 1);
	arg = take_input(c, v);
	if (arg.nb_philo <= 0 || arg.death_time <= 0 || arg.eat_time <= 0
		|| arg.sleep_time <= 0)
		return (write(1, "INVALID ARGUMENTS\n", 18), 1);
	if (init_mutex(&arg) == 1)
		return (write(1, "MUTEX ERROR\n", 12), 1);
	init_philo(&arg);
	if (init_thread(arg.philos, &arg) == 1)
		return (write(1, "THREADS ERROR\n", 14), 1);
	check_death(&arg);
	destroy_mutex(&arg);
	return (0);
}

void	destroy_mutex(t_input *inf)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&inf->eat);
	pthread_mutex_destroy(&inf->count);
	while (i < inf->nb_philo)
	{
		pthread_mutex_destroy(&inf->philos[i].fork);
		i++;
	}
}
