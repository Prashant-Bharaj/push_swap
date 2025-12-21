/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:15:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 17:55:27 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	copy_string(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

static char	*append_char(char *str, char c, int len)
{
	char	*new;

	new = malloc(len + 2);
	if (!new)
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (str)
	{
		copy_string(new, str, len);
		free(str);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

static int	read_char(char *c)
{
	return (read(0, c, 1));
}

static int	handle_eof(int bytes, int len, char **line)
{
	if (bytes == 0 && len == 0)
	{
		*line = NULL;
		return (0);
	}
	return (1);
}

int	read_line(char **line)
{
	char	c;
	char	*result;
	int		len;
	int		bytes;

	result = NULL;
	len = 0;
	bytes = read_char(&c);
	while (bytes > 0)
	{
		if (c == '\n')
			break ;
		result = append_char(result, c, len);
		if (!result)
			return (0);
		len++;
		bytes = read_char(&c);
	}
	if (!handle_eof(bytes, len, line))
		return (0);
	*line = result;
	return (1);
}
