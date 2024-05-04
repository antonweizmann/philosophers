/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:03:18 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 09:06:11 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eaten_enough(t_control *control)
{
	int	eaten_enough;

	eaten_enough = 0;
	
}

int	is_dead(t_control *control)
{
	int	i;

	i = 0;
	while (control->philos + i)
	{
		lock_mutex(&control->eating_lock, NULL, control);
		if (get_time() - control->philos[i].time_last_meal >= control->philos[i].time_to_die && control->philos[i].eating == 0)
			return (unlock_mutex(&control->eating_lock, NULL, control), ft_putphilo_msg("is dead", &control->philos[i]), 1);
		unlock_mutex(&control->eating_lock, NULL, control);
		i++;
	}
	return (0);
}

void	monitor_philo(void *param)
{
	int			i;
	t_control	*control;

	control = param;
	i = 0;
	while (1)
	{
		if (is_dead(control) || eaten_enough(control) || is_error(control))
		{
			lock_mutex(&control->dead_lock, NULL, control);
			control->dead = 1;
			unlock_mutex(&control->dead_lock, NULL, control);
		}

	}
}
