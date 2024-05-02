/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:51 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/02 11:34:05 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					total_meals;
	int					eating;
}	t_philo;

typedef struct s_control
{
	t_philo				*philos;
	int					dead;
}	t_control;

int						ft_atoi(const char *str);

#endif
