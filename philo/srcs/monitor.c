/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/06 17:22:43 by mabaffo          ###   ########.fr       */
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
				pthread_mutex_lock(&(phi->args->dmux));
				ft_death(ft_millisec(), &phi[i]);
				pthread_mutex_unlock(&(phi->args->dmux));
				return (NULL);
			}
		}
		if (full == phi->args->num)
		{
			pthread_mutex_lock(&(phi->args->dmux));
			phi->args->end = 1;
			pthread_mutex_lock(&(phi->args->dmux));
			return (NULL);
		}
	}
	return (NULL);
}
