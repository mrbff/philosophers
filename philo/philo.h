/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:19:29 by mabaffo           #+#    #+#             */
/*   Updated: 2023/01/18 16:09:55 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>

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

#endif
