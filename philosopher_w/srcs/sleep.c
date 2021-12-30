/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 01:43:18 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/23 04:00:29 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long	get_time(long sleep)
{
	int				old_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	old_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (old_time - sleep);
}

void	ft_pause(long sleep)
{
	long	this_time;
	long	start;

	start = get_time(0);
	this_time = start;
	while (sleep + start > this_time)
	{
		usleep(100);
		this_time = get_time(0);
	}
}
