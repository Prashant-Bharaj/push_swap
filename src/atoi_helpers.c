/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_positive_overflow(long result, char digit)
{
	if (result > (long)INT_MAX / 10)
		return (1);
	if (result == (long)INT_MAX / 10 && digit - '0' > INT_MAX % 10)
		return (1);
	return (0);
}

static int	check_negative_overflow(long result, char digit)
{
	if (result > (long)-(long)INT_MIN / 10)
		return (1);
	if (result == (long)-(long)INT_MIN / 10
		&& digit - '0' > -(INT_MIN % 10))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && check_positive_overflow(result, str[i]))
			return (0);
		if (sign == -1 && check_negative_overflow(result, str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}
