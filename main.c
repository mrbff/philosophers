# include "philo.h"

int main(int ac, char **av)
{
	t_phi	*phi;

	if (ft_check(ac, av))
		return (0);
	phi = ft_create_phils(ac, av);
	if (!phi)
		return (1);

}
