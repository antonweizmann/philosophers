/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:47 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/02 11:38:51 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int id, int *input)
{
	t_philo	philo;

	philo.id = id;
	philo.time_to_die = input[1];
	philo.time_to_eat = input[2];
	philo.time_to_sleep = input[3];
	if (input[4])
		philo.total_meals = input[4];



}

int	check_input(char **argv, int argc, t_control *control)
{
	int	num_philo;
	int	i;
	int	*input;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argv[i])
		{
			input[i] = ft_atoi(argv[i]);
			if (input[i] <= 0)
				return (-1);
			i++;
		}
		i = 0;
		control->philos = malloc(sizeof(t_philo) * input[0]);
		while (i < input[0])
			control->philos[i] = init_philo(i, input);
	}
	return (-1)
}

int	main(int argc, char **argv)
{
	t_control	control;

	if (check_input(argv, argc) == -1)
		return (1);
	init_structs(control, argv);
}
