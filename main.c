# include "philo.h"

static void	*death(long long time, t_phi *phi)
{
	printf("Philosopher %zu died at %lld\n", phi->id, time);
	pthread_mutex_lock(&(phi->args->dmux));
	phi->args->end = 1;
	pthread_mutex_unlock(&(phi->args->dmux));
	return (NULL);
}

static void	*r(void *p)
{
	t_phi			*phi;
	pthread_mutex_t	*next_mux;

	phi = (t_phi *)p;
	next_mux = &(phi - (phi->id - 1))[phi->id % phi->args->num].mutex;
	while (1)
	{
		if (phi->args->end)
			return (NULL);
		phi->alive = (ft_millisec() - phi->lst_meal) <= phi->args->todie;
		if (!(phi->alive))
			return (death(ft_millisec(), phi));
		printf("%zu is thinking at %lld\n", phi->id, ft_millisec());
		pthread_mutex_lock(&(phi->mutex));
		pthread_mutex_lock(next_mux);
		printf("%zu has taken a fork at %lld\n", phi->id, ft_millisec());
		printf("%zu is eating at %lld\n", phi->id, ft_millisec());
		if (phi->meals > 0)
				(phi->alive) = (--(phi->meals) != 0);
		usleep(phi->args->toeat);
		pthread_mutex_unlock(&(phi->mutex));
		pthread_mutex_unlock(next_mux);
		printf("%zu is sleeping at %lld\n", phi->id, ft_millisec());
		usleep(phi->args->tosleep);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_phi		*phi;
	pthread_t	*th;
	int			i;

	if (ft_check(ac, av))
		return (-1);
	phi = ft_create_phils(ac, av);
	if (!phi)
		return (1);
	th = malloc(sizeof(pthread_t) * phi->args->num);
	if (!th)
		return (2);
	i = -1;
	while (++i < phi->args->num)
		pthread_create(&th[i], NULL, r, &phi[i]);
	i = -1;
	while (++i < phi->args->num)
		pthread_join(th[i], NULL);
	return (0);
}
