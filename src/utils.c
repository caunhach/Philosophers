/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:41:53 by caunhach          #+#    #+#             */
/*   Updated: 2023/08/03 13:53:15 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == 32))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	long int	res;
	int			i;

	i = 0;
	res = 0;
	if (is_digit(str))
		return (-1);
	while (str[i] && str[i] == 32)
		i++;
	while (str[i] && str[i] != 32)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res < 0 || res > 2147483647)
		return (-1);
	return (res);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(50);
}

void	print_status(t_philo *philo, char *str)
{
	t_info	*info;

	info = philo->data;
	pthread_mutex_lock(&(info->print));
	if (!(info->die) && !(info->fed))
	{
		printf("%lli ", timestamp() - info->timestamp);
		printf("%d ", philo->id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(info->print));
}
