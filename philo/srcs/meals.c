/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 05:02:58 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/30 22:33:03 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	get_forks(t_philo *p)
{
	int		forks;

	forks = 0;
	if (!died(p))
	{
		if (p->stuff->nbr_philo != 1)
		{
			pthread_mutex_lock(p->r_fork);
			print(p, "has taken a fork\n");
			pthread_mutex_lock(&p->l_fork);
			print(p, "has taken a fork\n");
			p->forks = 2;
			forks += 2;
		}
		else if (p->stuff->nbr_philo == 1)
		{
			pthread_mutex_lock(&p->l_fork);
			print(p, "has taken a fork\n");
			ft_pause(p->stuff->ttd + 1);
			pthread_mutex_unlock(&p->l_fork);
			p->forks = 0;
		}
	}
	return (forks);
}

void	limit_meals(t_philo *p)
{
	if (p->stuff->last_ate != 0)
	{
		pthread_mutex_lock(&p->nb_meals);
		p->meals++;
		pthread_mutex_lock(&p->nb_meals);
	}
}

void	release_forks(t_philo *p)
{
	if (p->forks == 2)
	{
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		p->forks = 0;
	}
	else if (p->forks == 1)
	{
		pthread_mutex_unlock(&p->l_fork);
		p->forks = 0;
	}
}

void	eat(t_philo *p)
{
	int		forks;

	forks = get_forks(p);
	if (!died(p) && forks == 2)
	{
		print(p, "is eating\n");
		ft_pause(p->stuff->tte);
		limit_meals(p);
		pthread_mutex_lock(&p->time);
		p->start_time = get_time(0);
		pthread_mutex_unlock(&p->time);
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		p->forks = 0;
	}
	release_forks(p);
}
