/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			return (-1);
	}
	return (end);
}

int	validate_string_with_spaces(const char *str)
{
	int	start;
	int	found_token;
	int	result;

	start = 0;
	found_token = 0;
	while (str[start])
	{
		start = skip_whitespace(str, start);
		if (!str[start])
			break ;
		result = process_token(str, start, &found_token);
		if (result == -1)
			return (0);
		start = result;
	}
	if (!found_token)
		return (0);
	return (1);
}
