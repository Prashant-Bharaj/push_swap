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

static int	check_overflow(const char *str)
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

static int	validate_single_token(const char *str)
{
	int	j;

	if (!str || !str[0])
		return (0);
	j = 0;
	if (str[j] == '-' || str[j] == '+')
		j++;
	if (!str[j])
		return (0);
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
			return (0);
		j++;
	}
	if (check_overflow(str))
		return (0);
	return (1);
}

static int	skip_whitespace(const char *str, int pos)
{
	while (str[pos] == ' ' || (str[pos] >= 9 && str[pos] <= 13))
		pos++;
	return (pos);
}

static int	find_token_end(const char *str, int start)
{
	int	end;

	end = start;
	while (str[end] && str[end] != ' ' && (str[end] < 9 || str[end] > 13))
		end++;
	return (end);
}

static int	process_token(const char *str, int start, int *found_token)
{
	int	end;

	end = find_token_end(str, start);
	if (end > start)
	{
		*found_token = 1;
		if (!validate_single_token(str + start))
			return (0);
	}
	return (end);
}

static int	validate_string_with_spaces(const char *str)
{
	int	start;
	int	found_token;

	start = 0;
	found_token = 0;
	while (str[start])
	{
		start = skip_whitespace(str, start);
		if (!str[start])
			break ;
		start = process_token(str, start, &found_token);
	}
	if (!found_token)
		return (0);
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (validate_string_with_spaces(argv[i]) == 0)
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
