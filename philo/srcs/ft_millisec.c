/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_millisec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:24:16 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/09 21:24:56 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	ft_millisec(void)
{
	struct timeval	tp;
	long long		milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (milliseconds);
}
