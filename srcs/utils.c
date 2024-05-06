/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweizman <aweizman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:16:00 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/06 13:12:01 by aweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		negative;
	int		result;
	int		digit;

	negative = 0;
	result = 0;
	while (*str == 32 || *str == 9 || *str == 10
		|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == 43 || *str == 45)
		if (*str++ == 45)
			negative = 1;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		if ((!negative && (INT_MAX - digit) / 10 < result)
			|| (negative && (INT_MIN + digit) / 10 > result))
			return (-1);
		result = result * 10 + digit;
	}
	if (negative == 1)
		result = -result;
	return (result);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, sizeof(c));
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	else
	{
		ft_putchar_fd(nb + 48, fd);
		return ;
	}
	ft_putnbr_fd(nb % 10, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write (fd, s++, sizeof(*s));
}

void	ft_putphilo_msg(char *s, t_philo *philo)
{
	if (dead_check(philo))
		return ;
	lock_mutex(philo->writing_lock, philo, NULL);
	ft_putnbr_fd(get_time() - philo->start_time, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	unlock_mutex(philo->writing_lock, philo, NULL);
}
