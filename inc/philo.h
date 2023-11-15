/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:39:58 by caunhach          #+#    #+#             */
/*   Updated: 2023/08/02 16:43:14 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		tid;
	int				c_eat;
	int				id;
	int				l_id;
	int				r_id;
	long long		last_eat;
	struct s_info	*data;
}	t_philo;

typedef struct s_info
{
	int				die;
	int				fed;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	t_philo			philos[200];
	long long		timestamp;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
}	t_info;

void		take_fork(t_philo *philo);
void		philo_eat(t_philo *philo);
int			check_input(int argc, char **argv);
int			ft_error(char *error_msg);
int			init(t_info *info, int argc, char **argv);
int			init_philos(t_info *info);
int			init_mutex(t_info *info);
void		*routine(void *ptr);
void		check_death(t_info *info, t_philo *p);
int			philo_life(t_info *info);
int			ft_atoi(char *str);
long long	timestamp(void);
void		ft_usleep(int ms);
void		print_status(t_philo *philo, char *str);

#endif
