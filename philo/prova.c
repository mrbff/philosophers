# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
#include <unistd.h>

typedef struct s_arg
{
	size_t              num;//num of philo and forks
//in milliseconds
	size_t	            todie;//time that takes a philo to die, start from last meal or the biginning
	size_t	            toeat;//time that takes to eat, during this time they need to hold 2 forks
	size_t	            tosleep;//time that a philo spend to sleep
	//[optional]
	long long	        meals;//time for every philo to eat for the simulation stops
///    
    pthread_mutex_t     mutex1;
    pthread_mutex_t     mutex2;
    size_t              **idp1;
    size_t              **idp2;
}	t_arg;

void    init_args(t_arg *args, int ac, char **av)
{
    args->num = atoi(av[1]);
    args->todie = atoi(av[2]);
    args->toeat = atoi(av[3]);
    args->tosleep = atoi(av[4]);
    if (ac == 6)
        args->meals = atoi(av[5]);
    *(args->idp1) = malloc(sizeof(size_t *));
    *(args->idp2) = malloc(sizeof(size_t *));
}

long long    millisec(void)
{
    struct timeval tp;
    long long milliseconds;

    gettimeofday(&tp, NULL);
    milliseconds = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return (milliseconds);
}

void    *r1(void *p)
{   
    size_t *tmp;

    pthread_mutex_lock(&(((t_arg *)(p))->mutex1));
/*    tmp = *(((t_arg *)(p))->idp1);
    printf("1 at time %lld, philo %zu\n", millisec(), *tmp );
    free(tmp);*/
    printf("1\n");
    usleep(500);
    pthread_mutex_unlock(&(((t_arg *)(p))->mutex1));
    return (NULL);
}

void    *r2(void *p)
{
    size_t *tmp;

    pthread_mutex_lock(&(((t_arg *)(p))->mutex2));
/*    tmp = *(((t_arg *)(p))->idp2);
    printf("2 at time %lld, philo %zu\n", millisec(), *tmp );
    free(tmp);*/
    printf("2\n");
    usleep(500);
    pthread_mutex_unlock(&(((t_arg *)(p))->mutex2));
    return (NULL);
}

int main(int ac, char **av)
{
    t_arg       args;
    pthread_t   *phi;
    size_t      *tmp;
    size_t      i;

    if (ac != 6 && ac != 5)
        return (1);
    init_args(&args, ac, av);
    i = 0;
    printf("num %zu\n", args.num);
    phi = malloc(sizeof(pthread_t) * args.num);
    pthread_mutex_init(&(args.mutex1), NULL);
    pthread_mutex_init(&(args.mutex2), NULL);
    while (i < args.num)
    {
        tmp = malloc(sizeof(size_t));
        *tmp = i;
        if (i % 2)
        {
 //           *(args.idp1) = tmp;
            pthread_create(&phi[i], NULL, &r1, &args);
        }
        else
        {
   //         *(args.idp2) = tmp;
            pthread_create(&phi[i], NULL, &r2, &args);
        }
        i++;
    }
    i = 0;
    while (i < args.num)
    {
        pthread_join(phi[i], NULL);
        i++;
    }
    free(phi);
    free(*(args.idp1));
    free(*(args.idp2));
    pthread_mutex_destroy(&(args.mutex1));
    pthread_mutex_destroy(&(args.mutex2));
    sleep(1);
    return (0);
}