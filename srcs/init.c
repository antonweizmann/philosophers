/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweizman <aweizman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:41:51 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/06 15:34:33 by aweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philo (t_philo *philo, char **argv, t_control *control)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * MAX_PHILO);
	i = 0;
	init_forks(forks, ft_atoi(argv[1]));
	// pthread_mutex_init(&forks[0], NULL);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo[i].total_meals = ft_atoi(argv[5]);
		else
			philo[i].total_meals = -1;
		philo[i].eating = 0;
		philo[i].total_eaten_meals = 0;
		philo[i].time_last_meal = get_time();
		philo[i].start_time = get_time();
		philo[i].dead = &control->dead;
		philo[i].error = &control->error;
		philo[i].error_lock = &control->error_lock;
		philo[i].dead_lock = &control->dead_lock;
		philo[i].writing_lock = &control->writing_lock;
		philo[i].eating_lock = &control->eating_locks[i];
		pthread_mutex_init(philo[i].eating_lock, NULL);
		// if (i + 1 < ft_atoi(argv[1]))
		// 	pthread_mutex_init(&forks[i + 1], NULL);
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % ft_atoi(argv[1])];
		i++;
	}
}

void	init_control(t_control *control, t_philo *philo, pthread_mutex_t *eating_locks, int num_philo)
{
	control->dead = 0;
	control->error = 0;
	control->philos = philo;
	control->eating_locks = eating_locks;
	control->num_philo = num_philo;
	pthread_mutex_init(&control->error_lock, NULL);
	pthread_mutex_init(&control->dead_lock, NULL);
	pthread_mutex_init(&control->writing_lock, NULL);
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

int	check_input(char **argv, int argc)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0 || check_chars(argv[1]) == 1)
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
	else
		return (ft_putstr_fd("Invalid Number Of Arguments\n", 2), 1);
	return (0);
}
