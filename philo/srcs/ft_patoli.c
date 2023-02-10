/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patoli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:25:26 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/09 21:25:29 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long long	ft_patoli(const char *nptr)
{
	size_t			i;
	long long int	num;

	i = 0;
	num = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + nptr[i] - 48;
		i++;
	}
	if ((nptr[i]))
		return (-1);
	return (num);
}
