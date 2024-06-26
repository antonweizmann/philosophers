/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweizman <aweizman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:47 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/06 16:31:27 by aweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_control *control, int num_philo)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_philo, control) != 0)
		return (clean_up("Error whilst creating thread", control));
	i = 0;
	while (i < num_philo)
	{
		usleep(10);
		if (pthread_create(&control->philos[i].thread, NULL, philosopher, &control->philos[i]) != 0)
			return (clean_up("Error whilst creating thread", control));
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (clean_up("Error whilst joining thread", control));
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(control->philos[i].thread, NULL) != 0)
			return (clean_up("Error whilst joining thread", control));
		i++;
	}
	clean_up(NULL, control);
	return (0);
}
int	main(int argc, char **argv)
{
	t_control		control;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	eating_locks[MAX_PHILO];

	if (argc > 1)
	{
		if (check_input(argv, argc) == 1)
			return (1);
		if (ft_atoi(argv[1]) == 1)
		{
			ft_putstr_fd("0 1 has taken a fork\n", 1);
			ms_sleep(ft_atoi(argv[2]));
			ft_putnbr_fd(ft_atoi(argv[2]), 1);
			ft_putstr_fd(" 1 died\n", 1);
			return (0);
		}
		init_control(&control, philo, eating_locks, ft_atoi(argv[1]));
		init_philo(philo, argv, &control);
		return (start_threads(&control, ft_atoi(argv[1])));
	}
	return (1);
}
