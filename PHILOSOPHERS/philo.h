/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:10 by met-tahe          #+#    #+#             */
/*   Updated: 2023/02/13 11:59:12 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_input
{
	int				nb_philo;
	int				death_time;
	int				eat_time;
	time_t			start;
	int				died;
	int				sleep_time;
	int				m_eat;
	pthread_mutex_t	eat;
	pthread_mutex_t	count;
	struct s_philo	*philos;
}					t_input;

typedef struct s_philo
{
	time_t			last_meal;
	pthread_t		ph;
	pthread_mutex_t	fork;
	int				eat_time;
	int				time_sleep;
	int				rfork;
	int				lfork;
	time_t			start;
	int				m_eat;
	int				philo_id;
	int				m_count;
	t_input			*args;
	struct s_philo	*right_philo;
}					t_philo;

t_input				take_input(int c, char **v);
int					ft_atoi(const char *str);
int					check_arg(char **v);
int					init_philo(t_input *arg);
int					init_mutex(t_input *arg);
int					init_thread(t_philo *th, t_input *arg);
void				*routine(void *threads);
time_t				get_time(void);
time_t				time_delai(struct timeval delai, struct timeval start);
void				timer(time_t time);
void				destroy_mutex(t_input *inf);
int					check_death(t_input *arg);
int					check_m_eat(t_input *arg);
void				message(t_philo *phil, char *msg);
void				counter_lock(t_philo *new);
#endif
