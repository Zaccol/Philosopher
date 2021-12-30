/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:57:05 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/30 22:33:13 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <limits.h>

static int	ft_isspace(const char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str, int *ret, long res)
{
	int		sign;

	sign = 1;
	if (!(*str))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str < ':' && *str > '/'))
	{
		res = res * 10 + (*str - 48);
		str++;
		if ((res * sign) < INT_MIN || (res * sign) > INT_MAX)
			return (0);
	}
	if (*str && (*str >= ':' || *str <= '/'))
		return (0);
	*ret = (res * sign);
	return (1);
}
