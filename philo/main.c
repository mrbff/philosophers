#include "philo.h"
/*
int	main(int ac, char **ac)
{
	t_param	philo;

	ft_check(ac, av, &philo);

}*/
/*
void	*eat(void	*arg)
{
	
}

void	*sleep()

void	*repeat()
*/
int	main(int ac, char **av)
{
	pthread_t *ph;

	ph = phialloc();

	i = -1;
	while (++i < nphi)
	{
		if (pthread_create(&ph[i], NULL/*where return*/, &eat, NULL/*arg*/))
			ft_putstr_fd("Failed to create thread\n", 2);
	}
	i = -1;
	while (++i < nphi)
	{
		if (pthread_join(ph[i], NULL))
			ft_putstr_fd("Failed to join thread\n", 2);
	}
}
