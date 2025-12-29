/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:03 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:07:17 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_overflow(const char *str)
{
	int		len;
	int		sign;
	int		start;
	int		i;
	char	*max_str;
	char	*min_str;

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
	max_str = "2147483647";
	min_str = "2147483648";
	if (sign == 1)
	{
		len = 0;
		while (len < 10)
		{
			if (str[i + len] > max_str[len])
				return (1);
			if (str[i + len] < max_str[len])
				return (0);
			len++;
		}
	}
	else
	{
		len = 0;
		while (len < 10)
		{
			if (str[i + len] > min_str[len])
				return (1);
			if (str[i + len] < min_str[len])
				return (0);
			len++;
		}
	}
	return (0);
}

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		if (!argv[i][j])
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		if (check_overflow(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
