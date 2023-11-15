/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:38:14 by caunhach          #+#    #+#             */
/*   Updated: 2023/08/02 17:52:11 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		init_signal;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of arguments"));
	if (check_input(argc, argv))
		return (ft_error("Wrong arguments"));
	init_signal = init(&info, argc, argv);
	if (init_signal == 1)
		return (ft_error("fail to init"));
	else if (init_signal == 2)
		return (ft_error("Wrong arguments"));
	if (philo_life(&info) == 1)
		return (ft_error("Thread fail"));
}
