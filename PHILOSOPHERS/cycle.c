/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:58:06 by met-tahe          #+#    #+#             */
/*   Updated: 2023/02/13 11:58:08 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	counter_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->count);
	philo->m_count++;
	pthread_mutex_unlock(&philo->args->count);
}

void	message(t_philo *phil, char *msg)
{
	printf("%li %i %s\n", get_time() - phil->start, phil->philo_id, msg);
}

void	*routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (!(philo->philo_id % 2))
		usleep(1000);
	while (philo->m_count != philo->m_eat)
	{
		pthread_mutex_lock(&philo->fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_philo->fork);
		message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->args->eat);
		message(philo, "is eating");
		philo->last_meal = get_time() - philo->start;
		pthread_mutex_unlock(&philo->args->eat);
		counter_lock(philo);
		timer(philo->eat_time);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->right_philo->fork);
		message(philo, "is sleeping");
		timer(philo->time_sleep);
		message(philo, "is thinking");
	}
	return (NULL);
}

int	check_m_eat(t_input *arg)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	pthread_mutex_lock(&arg->count);
	if (arg->m_eat == -5)
	{
		pthread_mutex_unlock(&arg->count);
		return (0);
	}
	while (i < arg->nb_philo)
	{
		if (arg->philos[i++].m_count == arg->m_eat)
			counter++;
	}
	if (counter == arg->nb_philo)
		return (2);
	pthread_mutex_unlock(&arg->count);
	return (0);
}

int	check_death(t_input *arg)
{
	int	i;

	while (arg->died == 0)
	{
		i = 0;
		while (i < arg->nb_philo)
		{
			pthread_mutex_lock(&arg->eat);
			if (get_time() - arg->start
				- arg->philos[i].last_meal > arg->death_time)
			{
				arg->died = 1;
				printf("%li %i died\n", get_time() - arg->start, i + 1);
				break ;
			}
			pthread_mutex_unlock(&arg->eat);
			usleep(100);
			i++;
		}
		if (arg->died == 1)
			return (0);
		if (check_m_eat(arg) == 2)
			return (0);
	}
	return (0);
}
