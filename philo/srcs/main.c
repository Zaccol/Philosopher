/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:26:17 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/30 22:31:54 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <stdlib.h>

void	print(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->stuff->display);
	if (!died(p))
	{
		printf("%ld philosopher %d ", get_time(p->stuff->init_time), p->id);
		printf("%s", str);
	}
	pthread_mutex_unlock(&p->stuff->display);
}

int	died(t_philo *p)
{
	pthread_mutex_lock(&p->stuff->death);
	if (p->stuff->died)
	{
		pthread_mutex_unlock(&p->stuff->death);
		return (1);
	}
	pthread_mutex_unlock(&p->stuff->death);
	return (0);
}

int	last_meal_ate(t_philo *p)
{
	pthread_mutex_lock(&p->nb_meals);
	if (p->meals >= p->stuff->last_ate)
	{
		pthread_mutex_unlock(&p->nb_meals);
		return (1);
	}
	pthread_mutex_unlock(&p->nb_meals);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		ft_pause(1);
	pthread_mutex_lock(&p->nb_meals);
	if (p->stuff->last_ate > 0)
		p->meals = 0;
	pthread_mutex_unlock(&p->nb_meals);
	pthread_mutex_lock(&p->time);
	p->start_time = get_time(0);
	pthread_mutex_unlock(&p->time);
	while (!died(p) && !last_meal_ate(p))
	{
		eat(p);
		print(p, "is sleeping...\n");
		ft_pause(p->stuff->tts);
		print(p, "is thinking...\n");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			i;
	t_stuff		stuff;
	pthread_t	death;

	i = 0;
	control_parsing(&stuff, av, ac);
	stuff.init_time = get_time(0);
	while (i < stuff.nbr_philo)
	{
		pthread_create(&stuff.philo[i].t_id, NULL, routine, &stuff.philo[i]);
		pthread_create(&death, NULL, death_routine, &stuff.philo[i]);
		pthread_detach(death);
		i++;
	}
	i = 0;
	while (i < stuff.nbr_philo)
	{
		pthread_join(stuff.philo[i].t_id, NULL);
		i++;
	}
	end_free(&stuff);
	return (0);
}
