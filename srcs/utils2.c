/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweizman <aweizman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:49:50 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/06 15:52:57 by aweizman         ###   ########.fr       */
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
	if (ms > 5)
		usleep((ms - 5) * 1000);
	while ((get_time() - start) < ms)
		usleep(200);
	return (0);
}

void	lock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	// if (!philo)
	// {
	// 	if (pthread_mutex_lock(mutex))
	// 	{
	// 		pthread_mutex_lock(&control->error_lock);
	// 		control->error = 1;
	// 		pthread_mutex_unlock(&control->error_lock);
	// 	}
	// }
	// else
	// {
	// 	if (pthread_mutex_lock(mutex))
	// 	{
	// 		pthread_mutex_lock(philo->error_lock);
	// 		// ft_putphilo_msg("error", philo);
	// 		*philo->error = 1;
	// 		pthread_mutex_unlock(philo->error_lock);
	// 	}
	// }
	(void)philo;
	(void)control;
	pthread_mutex_lock(mutex);
}

void	unlock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control)
{
	// if (!philo)
	// {
	// 	if (pthread_mutex_unlock(mutex))
	// 	{
	// 		pthread_mutex_lock(&control->error_lock);
	// 		control->error = 1;
	// 		pthread_mutex_unlock(&control->error_lock);
	// 	}
	// }
	// else
	// {
	// 	if (pthread_mutex_unlock(mutex))
	// 	{
	// 		pthread_mutex_lock(philo->error_lock);
	// 		*philo->error = 1;
	// 		pthread_mutex_unlock(philo->error_lock);
	// 	}
	// }
	(void)philo;
	(void)control;
	pthread_mutex_unlock(mutex);
}

void	clean_up(char *str, t_control *control)
{
	int	i;

	i = 0;
	if (str)
		ft_putstr_fd(str, 2);

	pthread_mutex_destroy(&control->writing_lock);
	pthread_mutex_destroy(&control->error_lock);
	pthread_mutex_destroy(&control->dead_lock);

	while (i < control->num_philo)
	{
		pthread_mutex_destroy(control->philos[i].r_fork);
		pthread_mutex_destroy(&control->eating_locks[i]);
		i++;
	}
	exit(1);
}
