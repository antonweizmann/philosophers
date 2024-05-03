/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:41:51 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/03 13:22:55 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo (t_philo *philo, char **argv, t_control *control)
{
	int	i;
	pthread_mutex_t	forks[MAX_PHILO];

	i = 0;
	init_forks(forks, ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = argv[2];
		philo[i].time_to_eat = argv[3];
		philo[i].time_to_sleep = argv[4];
		if (argv[5])
			philo[i].total_meals = argv[5];
		philo[i].eating = 0;
		philo[i].total_eaten_meals = 0;
		philo[i].time_last_meal = get_time();
		philo[i].start_time = get_time();
		philo[i].dead = &(control->dead);
		philo[i].error = &control->error;
		philo[i].dead_lock = &(control->dead_lock);
		philo[i].writing_lock = &(control->writing_lock);
		philo[i].eating_lock = &(control->eating_lock);
		philo[i].l_fork = forks[i];
		if (i + 1 == 1)
			philo[i].r_fork = forks[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = forks[i - 1];
		i++;
	}
}

void	init_control(t_control *control, t_philo *philo)
{
	control->dead = 0;
	control->error = 0;
	control->philos = philo;
	pthread_mutex_init(&(control->dead_lock), NULL);
	pthread_mutex_init(&(control->writing_lock), NULL);
	pthread_mutex_init(&(control->eating_lock), NULL);
}

void	init_forks(pthread_mutex_t *forks, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
		pthread_mutex_init(&(forks[i++]), NULL);
}

int	check_chars(char *str)
{
	while(*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	check_input(char **argv, int argc, t_control *control)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) == 1)
		{
			printf("0 1 has taken a fork\n");
			sleep_ms(ft_atoi(argv[2]));
			printf("%i 1 died\n", ft_atoi(argv[2]));
			return (0);
		}
		if (ft_atoi(argv[1]) > MAX_PHILO || ft_atoi(argv[1]) <= 0 || check_chars(argv[1]) == 1)
			return (ft_putstr_fd("Invalid Number Of Philosophers\n", 2), 1);
		if (ft_atoi(argv[2]) <= 0 || check_chars(argv[2]) == 1)
			return (ft_putstr_fd("Invalid Time To Die\n", 2), 1);
		if (ft_atoi(argv[3]) <= 0 || check_chars(argv[3]) == 1)
			return (ft_putstr_fd("Invalid Time To Eat\n", 2), 1);
		if (ft_atoi(argv[4]) <= 0 || check_chars(argv[4]) == 1)
			return (ft_putstr_fd("Invalid Time To Sleep\n", 2), 1);
		if (argv[5] && (ft_atoi(argv[5]) < 0 || check_chars(argv[5]) == 1))
			return (ft_putstr_fd("Invalid Number Of Meals\n", 2), 1);
	}
	return (ft_putstr_fd("Invalid Number Of Arguments\n", 2), 1);

}
