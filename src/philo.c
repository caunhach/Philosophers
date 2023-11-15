/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:23:49 by caunhach          #+#    #+#             */
/*   Updated: 2023/08/06 23:58:29 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_philo *philo)
{
	t_info	*info;

	info = philo->data;
	pthread_mutex_lock(&(info->forks[philo->l_id]));
	print_status(philo, "has taken a fork");
	if (info->n_philo == 1)
	{
		ft_usleep(info->t_die * 2);
		return ;
	}
	pthread_mutex_lock(&(info->forks[philo->r_id]));
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	t_info	*info;

	info = philo->data;
	print_status(philo, " is eating\n");
	pthread_mutex_lock(&(info->meal_check));
	philo->last_eat = timestamp();
	(philo->c_eat)++;
	pthread_mutex_unlock(&(info->meal_check));
	ft_usleep(info->t_eat);
	pthread_mutex_unlock(&(info->forks[philo->l_id]));
	pthread_mutex_unlock(&(info->forks[philo->r_id]));
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(15);
	while (!(philo->data->die) && !(philo->data->fed))
	{
		take_fork(philo);
		philo_eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->t_sleep);
		print_status(philo, "is thinking");
	}
	return ((void *)0);
}

void	check_death(t_info *info, t_philo *p)
{
	int		i;
	int		fed;

	while (!info->fed)
	{
		fed = 0;
		i = -1;
		while (++i < info->n_philo && !(info->die))
		{
			pthread_mutex_lock(&(info->meal_check));
			if (info->n_eat != -1 && p[i].c_eat >= info->n_eat)
				fed++;
			if (timestamp() - p[i].last_eat > info->t_die)
			{
				print_status(&p[i], "died");
				info->die = 1;
			}
			pthread_mutex_unlock(&(info->meal_check));
			usleep(100);
		}
		if (fed == info->n_philo)
			info->fed = 1;
		if (info->die)
			break ;
	}
}

int	philo_life(t_info *info)
{
	int	i;

	i = -1;
	info->timestamp = timestamp();
	while (++i < info->n_philo)
	{
		info->philos[i].last_eat = timestamp();
		if (pthread_create(&(info->philos[i].tid), NULL \
		, &routine, &(info->philos[i])))
			return (1);
	}
	check_death(info, info->philos);
	i = -1;
	while (++i < info->n_philo)
		pthread_join(info->philos[i].tid, NULL);
	i = -1;
	while (++i < info->n_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->meal_check));
	return (0);
}
