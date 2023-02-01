#include "philo.h"

long long	ft_millisec(void)
{
	struct		timeval tp;
	long long	milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (milliseconds)
}
