#include "philo.h"

int ft_check(int ac, char **av)
{
    if (ac != 5 && ac != 6)
        return (1);
    if (ft_patoli(av[1]) <= 0)
        return (1);
    if (ft_patoli(av[2]) <= 0)
        return (1);
    if (ft_patoli(av[3]) <= 0)
        return (1);
    if (ft_patoli(av[4]) <= 0)
        return (1);
    if (ac == 6)
    {
        if (ft_patoli(av[5]) <= 0)
            return (1);
    }
    return (0);
}

static void    init_args(t_args *args, int ac, char **av)
{
    args->num = ft_patoli(av[1]);
    args->todie = ft_patoli(av[2]);
    args->toeat = ft_patoli(av[3]);
    args->tosleep = ft_patoli(av[4]);
}

t_phi    *ft_create_phils(t_phi *phi,  int ac, char **av)
{
    t_args   *args;
    t_phi    *phils;
    int     i;

    args = malloc(sizeof(t_args));
    if (!args)
        return (NULL);
    init_args(args, ac, av);
    phi = malloc(sizeof(t_phi) * args->num);
    if (!phi)
    {
        free(args);
        return (NULL);
    }
    i = 0;
    while (i < args->num)
    {
        phils[i]->args = args;
        if (ac == 6)
           phils[i]->meals = ft_patoli(av[5]);
        else
            phils[i]->meals = -1;
        phils[i]->id = i + 1;
        pthread_mutex_init(&(phils[i]->mutex), NULL);
    }
    return (phils);
}
