/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/11 19:13:48 by mabaffo          ###   ########.fr       */
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
	long long		meals;
	size_t			id;
	long long		lst_meal;
	pthread_mutex_t	lmmux;
	pthread_mutex_t	mmux;
	pthread_mutex_t	mutex;
}	t_phi;

long long	ft_patoli(const char *nptr);
int			ft_check(int ac, char **av);
t_phi		*ft_create_phils(int ac, char **av);
long long	ft_millisec(void);
void		ft_print(const char *s, const t_phi *phi);
void		*ft_monitor(void *p);

#endif
