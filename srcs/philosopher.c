/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:32 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 10:01:13 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	lock_mutex(philo->dead_lock, philo, NULL);
	if (*philo->dead)
		return(unlock_mutex(philo->dead_lock, philo, NULL), 1);
	unlock_mutex(philo->dead_lock, philo, NULL);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	lock_mutex(&philo->r_fork, philo, NULL);
	ft_putphilo_msg("has taken a fork", philo);
	lock_mutex(&philo->l_fork, philo, NULL);
	ft_putphilo_msg("has taken a fork", philo);
	if (dead_check(philo))
		return (unlock_mutex(&philo->r_fork, philo, NULL), unlock_mutex(&philo->l_fork, philo, NULL));
	philo->eating = 1;
	ft_putphilo_msg("is eating", philo);
	lock_mutex(philo->eating_lock, philo, NULL);
	philo->time_last_meal = get_time();
	philo->total_eaten_meals += 1;
	unlock_mutex(philo->eating_lock, philo, NULL);
	usleep(philo->time_to_eat);
	philo->eating = 0;
	unlock_mutex(&philo->r_fork, philo, NULL);
	unlock_mutex(&philo->l_fork, philo, NULL);

}

void	philo_sleep(t_philo *philo)
{
	ft_putphilo_msg("is sleeping", philo);
	usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	ft_putphilo_msg("is thinking", philo);
}

void	*philosopher(void *param)
{
	t_philo *philo;

	philo = param;
	if (philo->id % 2 == 0)
		usleep(1);
	ft_putnbr_fd(*philo->dead, 2);
	while (!dead_check(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

