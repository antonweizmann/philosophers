/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:49:50 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 13:27:28 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}
int	ms_sleep(unsigned int ms)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}
void	lock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	if (!philo)
	{
		if (pthread_mutex_lock(mutex))
		{
			pthread_mutex_lock(&control->error_lock);
			control->error = 1;
			pthread_mutex_unlock(&control->error_lock);
		}
	}
	else
	{
		if (pthread_mutex_lock(mutex))
		{
			pthread_mutex_lock(philo->error_lock);
			*philo->error = 1;
			pthread_mutex_unlock(philo->error_lock);
		}
	}
}

void	unlock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	if (!philo)
	{
		if (pthread_mutex_unlock(mutex))
			control->error = 1;
	}
	else
	{
		if (pthread_mutex_unlock(mutex))
			*philo->error = 1;
	}
}

void	clean_up(char *str, t_control *control)
{
	int	i;

	i = 0;
	ft_putstr_fd(str, 2);
	pthread_mutex_destroy(&control->writing_lock);
	pthread_mutex_destroy(&control->eating_lock);
	pthread_mutex_destroy(&control->error_lock);
	pthread_mutex_destroy(&control->dead_lock);
	while (i < control->num_philo)
		pthread_mutex_destroy(control->philos[i++].r_fork);
	exit(1);
}
