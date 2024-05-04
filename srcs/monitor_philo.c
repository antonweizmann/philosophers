/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:03:18 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 10:08:58 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eaten_enough(t_control *control)
{
	int	eaten_enough;
	int	i;

	i = 0;
	eaten_enough = 0;
	while (i < control->num_philo)
	{
		lock_mutex(&control->eating_lock, NULL, control);
		if (control->philos[i].total_eaten_meals >= control->philos[i].total_meals)
			eaten_enough++;
		unlock_mutex(&control->eating_lock, NULL, control);
		i++;
	}
	if (eaten_enough == control->num_philo)
		return (1);
	return (0);
}

int	is_dead(t_control *control)
{
	int	i;

	i = 0;
	while (i < control->num_philo)
	{
		lock_mutex(&control->eating_lock, NULL, control);
		if (get_time() - control->philos[i].time_last_meal >= control->philos[i].time_to_die && control->philos[i].eating == 0)
			return (unlock_mutex(&control->eating_lock, NULL, control), ft_putphilo_msg("is dead", &control->philos[i]), 1);
		unlock_mutex(&control->eating_lock, NULL, control);
		i++;
	}
	return (0);
}

int	is_error(t_control *control)
{
	lock_mutex(&control->error_lock, NULL, control);
	if (control->error)
		return (unlock_mutex(&control->error_lock, NULL, control), 1);
	unlock_mutex(&control->error_lock, NULL, control);
	return (0);
}

void	*monitor_philo(void *param)
{
	t_control	*control;

	control = param;
	usleep(500);
	while (1)
	{
		if (is_dead(control) || is_error(control))
		{
			lock_mutex(&control->dead_lock, NULL, control);
			control->dead = 1;
			unlock_mutex(&control->dead_lock, NULL, control);
			break;
		}
	}
	return (NULL);
}
