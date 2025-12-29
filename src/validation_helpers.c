/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	compare_with_limit(const char *str, int start, const char *limit)
{
	int	len;

	len = 0;
	while (len < 10)
	{
		if (str[start + len] > limit[len])
			return (1);
		if (str[start + len] < limit[len])
			return (0);
		len++;
	}
	return (0);
}

static int	check_length_and_compare(const char *str, int start, int sign)
{
	int		i;
	int		len;
	char	*limit;

	i = start;
	while (str[i] == '0')
		i++;
	len = 0;
	while (str[i + len] >= '0' && str[i + len] <= '9')
		len++;
	if (len > 10)
		return (1);
	if (len < 10)
		return (0);
	if (sign == 1)
		limit = "2147483647";
	else
		limit = "2147483648";
	return (compare_with_limit(str, i, limit));
}

int	check_overflow(const char *str)
{
	int	start;
	int	sign;

	start = 0;
	sign = 1;
	while (str[start] == ' ' || (str[start] >= 9 && str[start] <= 13))
		start++;
	if (str[start] == '-' || str[start] == '+')
	{
		if (str[start] == '-')
			sign = -1;
		start++;
	}
	return (check_length_and_compare(str, start, sign));
}
