/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:29:58 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/09 21:59:16 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

struct s_sup
{
	int			end;
	long long	lm;
};

static int	fck_norme2(t_phi *phi, size_t *full, struct s_sup *s)
{
	long long	i;

	i = -1;
	while (++i < (long long)phi->args->num)
	{
		pthread_mutex_lock(&(phi[i].mmux));
		if (phi[i].meals == 0)
			(*full)++;
		pthread_mutex_unlock(&(phi[i].mmux));
		pthread_mutex_lock(&(phi[i].lmmux));
		s->lm = phi[i].lst_meal;
		pthread_mutex_unlock(&(phi[i].lmmux));
		if (ft_millisec() - s->lm > (long long)phi[i].args->todie)
		{
			ft_print("%lld %zu died\n", &phi[i]);
			pthread_mutex_lock(&(phi->args->dmux));
			phi->args->end = 1;
			pthread_mutex_unlock(&(phi->args->dmux));
			return (1);
		}
	}
	return (0);
}

void	*ft_monitor(void *p)
{
	t_phi			*phi;
	size_t			full;
	struct s_sup	s;

	phi = (t_phi *)p;
	s.end = 0;
	while (!s.end)
	{
		full = 0;
		if (fck_norme2(phi, &full, &s))
			return (NULL);
		if (full == phi->args->num)
		{
			pthread_mutex_lock(&(phi->args->dmux));
			phi->args->end = 1;
			pthread_mutex_unlock(&(phi->args->dmux));
			return (NULL);
		}
		pthread_mutex_lock(&(phi->args->dmux));
		s.end = phi->args->end;
		pthread_mutex_unlock(&(phi->args->dmux));
	}
	return (NULL);
}
