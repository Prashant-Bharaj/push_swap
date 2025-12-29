/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:10 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:11 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	error_exit(t_data *data, char *message)
{
	if (message)
		write(2, message, get_strlen(message));
	if (data)
		free_data(data);
	exit(1);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->a)
		free_stack(data->a);
	if (data->b)
		free_stack(data->b);
	if (data->a)
		free(data->a);
	if (data->b)
		free(data->b);
	if (data->arr)
		free(data->arr);
}
