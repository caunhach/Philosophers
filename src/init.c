/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:26:48 by caunhach          #+#    #+#             */
/*   Updated: 2023/08/03 14:29:08 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(info->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(info->print), NULL))
		return (1);
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].c_eat = 0;
		info->philos[i].l_id = i;
		info->philos[i].r_id = (i + 1) % info->n_philo;
		info->philos[i].last_eat = 0;
		info->philos[i].data = info;
	}
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->die = 0;
	info->fed = 0;
	if (argc == 6)
		info->n_eat = ft_atoi(argv[5]);
	else
		info->n_eat = -1;
	if (info->n_philo > 200 || info->t_die < 60 || \
	info->t_eat < 60 || info->t_sleep < 60 || \
	info->n_eat == 0)
		return (2);
	if (init_mutex(info))
		return (1);
	init_philos(info);
	return (0);
}
