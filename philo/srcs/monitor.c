/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/06 12:42:37 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_monitor(void *p)
{
	long long	i;
	t_phi		*phi;
	size_t		full;

	phi = (t_phi *)p;
	while (!(phi->args->end))
	{
		i = -1;
		full = 0;
		while(++i < (long long)phi->args->num)
		{
			if (phi[i].meals == 0)
				full++;
			if (ft_millisec() - phi[i].lst_meal > (long long)phi[i].args->todie)
			{
				ft_death(ft_millisec(), &phi[i]);
				return (NULL);
			}
		}
		if (full == phi->args->num)
		{
			phi->args->end = 1;
			return (NULL);
		}
	}
	return (NULL);
}
