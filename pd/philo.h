/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/07 15:56:50 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

	typedef struct s_args
	{
		size_t			num;
		size_t			todie;
		size_t			toeat;
		size_t			tosleep;
		int				end;
		pthread_mutex_t	dmux;
		pthread_mutex_t	pmux;
	}	t_args;

	typedef struct s_phi
	{
		t_args			*args;
		long long		meals;//[optional], -1 if not exist
		size_t			id;
		long long		lst_meal;
		pthread_mutex_t	mutex;
	}	t_phi;

long long	ft_patoli(const char *nptr);
int			ft_check(int ac, char **av);
t_phi		*ft_create_phils(int ac, char **av);
long long	ft_millisec(void);
void		ft_print(const char *s, const t_phi *phi);
//void		*ft_death(long long time, t_phi *phi);
void		*ft_monitor(void *p);

#endif
/*
typedef struct s_param
{
	size_t	number;//philo and forks
	//in milliseconds
	size_t	todie;//time that takes a philo to die, start from last meal or the biginning
	size_t	toeat;//time that takes to eat, during this time they need to hold 2 forks
	size_t	tosleep;//time that a philo spend to sleep
	//[optional]
	long long	meals;//time for every philo to eat for the simulation stops
}	t_param;
*/
