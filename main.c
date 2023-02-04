/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:26:41 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/04 17:51:25 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*ft_death(long long time, t_phi *phi)
{
	printf("%lld %zu died\n", time, phi->id);
	pthread_mutex_lock(&(phi->args->dmux));
	pthread_mutex_unlock(&(phi->mutex));
	phi->args->end = 1;
	pthread_mutex_unlock(&(phi->args->dmux));
	return (NULL);
}

static void	ft_print(char *s, size_t id, int end)
{
	if (!end)
		printf(s, ft_millisec(), id);
}

static void	*r(void *p)
{
	t_phi			*phi;
	pthread_mutex_t	*next_mux;

	phi = (t_phi *)p;
	next_mux = &(phi - (phi->id - 1))[phi->id % phi->args->num].mutex;
	while (!(phi->args->end))
	{
		long long m = ft_millisec();
		printf("%lld - %lld = %lld\n", m, phi->lst_meal, m - phi->lst_meal);
		printf("to die = %zu\n", phi->args->todie);
		if (ft_millisec() - phi->lst_meal > (long long)phi->args->todie)
			ft_death(ft_millisec(), phi);
		ft_print("%lld %zu is thinking\n", phi->id, phi->args->end);
		pthread_mutex_lock(&(phi->mutex));
		pthread_mutex_lock(next_mux);
		ft_print("%lld %zu has taken a fork\n", phi->id, phi->args->end);
		phi->lst_meal = ft_millisec();
		ft_print("%lld %zu is eating\n", phi->id, phi->args->end);
		usleep(phi->args->toeat);
		if (phi->meals > 0)
			(phi->meals)--;
		pthread_mutex_unlock(&(phi->mutex));
		pthread_mutex_unlock(next_mux);
		ft_print("%lld %zu is sleeping\n", phi->id, phi->args->end);
		usleep(phi->args->tosleep);
	}
	return (NULL);
}

static void	freephi(t_phi *phi)
{
	free(phi->args);
	free(phi);
}

int	main(int ac, char **av)
{
	t_phi		*phi;
	pthread_t	*th;
	pthread_t	undertaker;
	long long			i;

	if (ft_check(ac, av))
		return (-1);
	phi = ft_create_phils(ac, av);
	if (!phi)
		return (1);
	th = malloc(sizeof(pthread_t) * phi->args->num);
	if (!th)
		return (2);
	i = -1;
	while (++i < (long long)phi->args->num)
		pthread_create(&th[i], NULL, r, (void *)&phi[i]);
	pthread_create(&undertaker, NULL, ft_monitor, (void *)phi);
	i = -1;
	while (++i < (long long)phi->args->num)
		pthread_join(th[i], NULL);
	pthread_join(undertaker, NULL);
	i = -1;
	while (++i < (long long)phi->args->num)
		pthread_mutex_destroy(&(phi[i].mutex));
	pthread_mutex_destroy(&(phi->args->dmux));
	freephi(phi);
	free(th);
	return (0);
}
