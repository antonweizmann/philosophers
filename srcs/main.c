/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:47 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 09:55:37 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_control *control, int num_philo)
{
	int			i;
	pthread_t	monitor;

	control->num_philo = num_philo;
	if (pthread_create(&monitor, NULL, &monitor_philo, control) != 0)
		clean_up("Error whilst creating thread", control);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&control->philos[i].thread, NULL, philosopher, &control->philos[i]) != 0)
			clean_up("Error whilst creating thread", control);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		clean_up("Error whilst joining thread", control);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(control->philos[i].thread, NULL) != 0)
			clean_up("Error whilst joining thread", control);
		i++;
	}
	return ;
}
int	main(int argc, char **argv)
{
	t_control	control;
	t_philo		philo[MAX_PHILO];

	if (check_input(argv, argc) == 1)
		return (1);
	init_control(&control, philo);
	init_philo(philo, argv, &control);
	start_threads(&control, ft_atoi(argv[1]));
	// clean_up(NULL, &control);
}