/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweizman <aweizman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:08:51 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/06 16:26:32 by aweizman         ###   ########.fr       */
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

# define MAX_PHILO 220

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					total_meals;
	int					eating;
	int					total_eaten_meals;
	long		time_last_meal;
	unsigned int		start_time;
	int					*dead;
	int					*error;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*error_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eating_lock;
	pthread_mutex_t		*writing_lock;
}	t_philo;

typedef struct s_control
{
	t_philo				*philos;
	int					num_philo;
	int					dead;
	int					error;
	pthread_mutex_t		*forks;
	pthread_mutex_t		error_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		*eating_locks;
	pthread_mutex_t		writing_lock;
}	t_control;

// Utils
int						ft_atoi(const char *str);
void					ft_putstr_fd(char *s, int fd);
unsigned int			get_time(void);
void					ft_putphilo_msg(char *s, t_philo *philo);
int						clean_up(char *str, t_control *control);
void					ft_putnbr_fd(int n, int fd);
int						ms_sleep(unsigned int ms);
// Mutex
void					lock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control);
void					unlock_mutex(pthread_mutex_t *mutex, t_philo *philo, t_control *control);

// Init
void					init_philo (t_philo *philo, char **argv, t_control *control);
void					init_control(t_control *control, t_philo *philo, pthread_mutex_t *eating_locks, int num_philo);
int						check_input(char **argv, int argc);


// Philosopher
void					*philosopher(void *param);
int						dead_check(t_philo *philo);

// Monitor
void					*monitor_philo(void *param);
#endif
