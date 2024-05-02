/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:16:00 by antonweizma       #+#    #+#             */
/*   Updated: 2024/05/02 11:18:58 by antonweizma      ###   ########.fr       */
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

