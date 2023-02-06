/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:26:41 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/06 12:52:03 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	*ft_death(long long time, t_phi *phi)
{
	printf("%lld %zu died\n", time, phi->id);
	pthread_mutex_lock(&(phi->args->dmux));
	phi->args->end = 1;
	pthread_mutex_unlock(&(phi->args->dmux));
	return (NULL);
}

static void	ft_print(char *s, t_phi *phi, int end)
{
	if (!end)
	{
		pthread_mutex_lock(&(phi->args->pmux));
		printf(s, ft_millisec(), phi->id);
		pthread_mutex_unlock(&(phi->args->pmux));
	}
}

static void	*r(void *p)
{
	t_phi			*phi;
	pthread_mutex_t	*next_mux;

	phi = (t_phi *)p;
	next_mux = &(phi - (phi->id - 1))[phi->id % phi->args->num].mutex;
	while (!(phi->args->end))
	{
		if (ft_millisec() - phi->lst_meal > (long long)phi->args->todie)
			ft_death(ft_millisec(), phi);
		ft_print("%lld %zu is thinking\n", phi, phi->args->end);
		pthread_mutex_lock(&(phi->mutex));
		pthread_mutex_lock(next_mux);
		ft_print("%lld %zu has taken a fork\n", phi, phi->args->end);
		phi->lst_meal = ft_millisec();
		ft_print("%lld %zu is eating\n", phi, phi->args->end);
		usleep(phi->args->toeat * 1000);
		if (phi->meals > 0)
			(phi->meals)--;
		pthread_mutex_unlock(&(phi->mutex));
		pthread_mutex_unlock(next_mux);
		ft_print("%lld %zu is sleeping\n", phi, phi->args->end);
		usleep(phi->args->tosleep * 1000);
	}
	return (NULL);
}

static void	freendstrymux(t_phi *phi, pthread_t *th)
{
	long long	i;

	i = -1;
	while (++i < (long long)phi->args->num)
		pthread_mutex_destroy(&(phi[i].mutex));
	pthread_mutex_destroy(&(phi->args->dmux));
	pthread_mutex_destroy(&(phi->args->pmux));
	free(phi->args);
	free(phi);
	free(th);
}

int	main(int ac, char **av)
{
	t_phi		*phi;
	pthread_t	*th;
	pthread_t	undertaker;
	long long	i;

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
	freendstrymux(phi, th);
	return (0);
}
/*
 * printf("%zu: phi[0].id = %zu\n", phi->id, (phi - (phi->id - 1))->id);
 * printf("to die = %zu\n", phi->args->todie);
 */
