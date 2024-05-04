/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:49:50 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 08:46:35 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	lock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	if (!philo)
		if (pthread_mutex_lock(mutex))
			control->error = 1;
	else
		if (pthread_mutex_lock(mutex))
			*philo->error = 1;
}

void	unlock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	if (!philo)
		if (pthread_mutex_unlock(mutex))
			control->error = 1;
	else
		if (pthread_mutex_unlock(mutex))
		*philo->error = 1;
}
