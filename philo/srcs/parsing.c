/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:52:25 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/31 02:36:11 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Error param.\n");
		exit(EXIT_FAILURE);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] > 47 && av[i][j] < 58))
				return (parse(0, NULL));
			j++;
		}
		if (ft_strlen(av[i]) > 9)
			return (parse(0, NULL));
		i++;
	}
	return (0);
}

void	init_stuff(t_stuff *stuff, char **av, int ac)
{
	if (!(ft_atoi(av[1], &stuff->nbr_philo, 0)))
		error_value();
	if (!(ft_atoi(av[2], &stuff->ttd, 0)))
		error_value();
	if (!(ft_atoi(av[3], &stuff->tte, 0)))
		error_value();
	if (!(ft_atoi(av[4], &stuff->tts, 0)))
		error_value();
	if (ac == 6)
	{
		if (!(ft_atoi(av[5], &stuff->last_ate, 0)))
			error_value();
	}
	else
		stuff->last_ate = 0;
	stuff->init_time = 0;
	stuff->died = 0;
	if (stuff->nbr_philo < 1)
	{
		ft_putstr("Error : not enough philo\n");
		exit(EXIT_FAILURE);
	}
}

void	init_philo(t_stuff *stuff)
{
	int	i;

	i = 0;
	stuff->philo = malloc(sizeof(t_philo) * stuff->nbr_philo);
	if (!stuff->philo)
		failed_malloc();
	pthread_mutex_init(&stuff->display, NULL);
	pthread_mutex_init(&stuff->death, NULL);
	pthread_mutex_init(&stuff->begin, NULL);
	while (i < stuff->nbr_philo)
	{
		stuff->philo[i].start_time = get_time(0);
		stuff->philo[i].id = i + 1;
		stuff->philo[i].last_ate = 0;
		stuff->philo[i].meals = -1;
		if (i == stuff->nbr_philo - 1 && stuff->nbr_philo != 1)
			stuff->philo[i].r_fork = &stuff->philo[0].l_fork;
		else
			stuff->philo[i].r_fork = &stuff->philo[i + 1].l_fork;
		stuff->philo[i].stuff = stuff;
		pthread_mutex_init(&stuff->philo[i].time, NULL);
		pthread_mutex_init(&stuff->philo[i].nb_meals, NULL);
		pthread_mutex_init(&stuff->philo[i].l_fork, NULL);
		i++;
	}
}

void	control_parsing(t_stuff *stuff, char **av, int ac)
{
	parse(ac, av);
	init_stuff(stuff, av, ac);
	init_philo(stuff);
}
