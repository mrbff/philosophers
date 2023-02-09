/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/09 20:00:20 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_monitor(void *p)
{
	long long	i;
	t_phi		*phi;
	size_t		full;
	int			end;
	long long	lm;

	phi = (t_phi *)p;
	end = 0;
	while (!end)
	{
		i = -1;
		full = 0;
		while(++i < (long long)phi->args->num)
		{
			pthread_mutex_lock(&(phi[i].mmux));
			if (phi[i].meals == 0)
				full++;
			pthread_mutex_unlock(&(phi[i].mmux));
			pthread_mutex_lock(&(phi[i].lmmux));
			lm = phi[i].lst_meal;
			pthread_mutex_unlock(&(phi[i].lmmux));
			if (ft_millisec() - lm > (long long)phi[i].args->todie)
			{
//				pthread_mutex_lock(&(phi->args->dmux));
				ft_print("%lld %zu died\n", &phi[i]);
//				ft_death(ft_millisec(), &phi[i]);
				pthread_mutex_lock(&(phi->args->dmux));
				phi->args->end = 1;
				pthread_mutex_unlock(&(phi->args->dmux));
				return (NULL);
			}
		}
		if (full == phi->args->num)
		{
			pthread_mutex_lock(&(phi->args->dmux));
			phi->args->end = 1;
			pthread_mutex_unlock(&(phi->args->dmux));
			return (NULL);
		}
		pthread_mutex_lock(&(phi->args->dmux));
		end = phi->args->end;
		pthread_mutex_unlock(&(phi->args->dmux));
	}
	return (NULL);
}
