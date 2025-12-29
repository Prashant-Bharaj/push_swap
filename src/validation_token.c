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

int	copy_token_with_sign(const char *str, int start, int end, char *temp);

static int	validate_token_substring(const char *str, int start, int end)
{
	char	temp[12];
	int		len;

	if (!str || start >= end)
		return (0);
	len = end - start;
	if (len > 11)
		return (0);
	if (!copy_token_with_sign(str, start, end, temp))
		return (0);
	return (!check_overflow(temp));
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
		if (!validate_token_substring(str, start, end))
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
