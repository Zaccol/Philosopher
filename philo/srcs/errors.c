/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:35:28 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/22 23:04:54 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	failed_malloc(void)
{
	ft_putstr("Error : Malloc failed");
	exit(EXIT_FAILURE);
}

void	error_value(void)
{
	ft_putstr("Error : Value param");
	exit(EXIT_FAILURE);
}

void	end_free(t_stuff *stuff)
{
	free(stuff->philo);
}
