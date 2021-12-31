/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 04:23:10 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/31 02:18:21 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*death_routine(void *philo)
{
	t_philo		*p;
	long long	time;

	p = (t_philo *)philo;
	ft_pause(2);
	while (!died(p) && !last_meal_ate(p))
	{
		pthread_mutex_lock(&p->time);
		pthread_mutex_lock(&p->stuff->display);
		time = get_time(p->start_time);
		if (time > p->stuff->ttd && !died(p) && !last_meal_ate(p))
		{
			pthread_mutex_lock(&p->stuff->death);
			p->stuff->died = 1;
			pthread_mutex_unlock(&p->stuff->death);
			printf("%ld philosopher %d is dead\n",
				get_time(p->stuff->init_time), p->id);
		}
		pthread_mutex_unlock(&p->stuff->display);
		pthread_mutex_unlock(&p->time);
		ft_pause(2);
	}
	return (NULL);
}
