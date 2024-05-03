/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:32 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/03 12:58:33 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	lock_mutex(philo->dead_lock, philo);
	if (philo->dead)
		return(unlock_mutex(philo->dead_lock, philo), 1);
	unlock_mutex(philo->dead_lock, philo);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	lock_mutex(&philo->r_fork, philo);
	ft_putphilo_msg("has taken a fork", philo);
	lock_mutex(&philo->l_fork, philo);
	ft_putphilo_msg("has taken a fork", philo);
	if (dead_check)
		return (unlock_mutex(&philo->r_fork, philo), unlock_mutex(&philo->l_fork, philo), 1);
	philo->eating = 1;
	ft_putphilo_msg("is eating", philo);
	lock_mutex(philo->eating_lock, philo);
	philo->time_last_meal = get_time();
	philo->total_eaten_meals += 1;
	unlock_mutex(philo->eating_lock, philo);
	usleep(philo->time_to_eat);
	philo->eating = 0;
	unlock_mutex(&philo->r_fork, philo);
	unlock_mutex(&philo->l_fork, philo);

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

void	philosopher(void *param)
{
	t_philo *philo;

	philo = param;
	if (philo->id % 2 == 0)
		usleep(1);
	while(!dead_check(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

