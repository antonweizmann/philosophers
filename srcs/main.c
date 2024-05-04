/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:47 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 08:34:14 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_control *control, int num_philo)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_philo, &control) != 0)
		clean_up("Error: Thread Creation", control);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&control->philos[i].thread, NULL, &philosopher, &control->philos[i]) != 0)
			clean_up("Error: Thread Creation", control);
		i++;
	}
	if (pthread_join(&monitor, NULL) != 0)
		clean_up("Error: Thread Joining", control);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(&control->philos[i].thread, NULL) != 0)
			clean_up("Error: Thread Joining", control);
		i++;
	}
	return ;
}
int	main(int argc, char **argv)
{
	t_control	control;
	t_philo		philo[MAX_PHILO];

	if (check_input(argv, argc, &control) == 1)
		return (1);
	init_control(&control, philo);
	init_philo(philo, argv, &control);
	start_threads(&control, ft_atoi(argv[1]));

}
