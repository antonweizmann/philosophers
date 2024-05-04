/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:51 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/04 08:59:03 by antonweizma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					total_meals;
	int					eating;
	int					total_eaten_meals;
	unsigned int		time_last_meal;
	unsigned int		start_time;
	int					*dead;
	int					*error;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eating_lock;
	pthread_mutex_t		*writing_lock;
}	t_philo;

typedef struct s_control
{
	t_philo				*philos;
	int					dead;
	int					error;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		eating_lock;
	pthread_mutex_t		writing_lock;
}	t_control;

// Utils
int						ft_atoi(const char *str);
void					ft_putstr_fd(char *s, int fd);
unsigned int			get_time(void);
void					ft_putphilo_msg(char *s, t_philo *philo);

// Mutex
void					lock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control);
void					unlock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control);

// Init
void					init_philo (t_philo *philo, char **argv, t_control *control);
void					init_control(t_control *control, t_philo *philo);
int						check_input(char **argv, int argc, t_control *control);


// Philosopher
void					philosopher(void *param);

// Monitor
void					monitor_philo(t_control *control);
#endif
