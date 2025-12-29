/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:27 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:07:03 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*get_index_array(t_stack *stack, int *size)
{
	int				*arr;
	t_stack_node	*current;
	int				i;

	*size = stack->size;
	arr = malloc(sizeof(int) * *size);
	if (!arr)
		return (NULL);
	current = stack->top;
	i = 0;
	while (current && i < *size)
	{
		arr[i] = current->index;
		current = current->next;
		i++;
	}
	return (arr);
}

int	find_max_index(int *dp, int size)
{
	int	max_idx;
	int	max_val;
	int	i;

	max_idx = 0;
	max_val = dp[0];
	i = 1;
	while (i < size)
	{
		if (dp[i] > max_val)
		{
			max_val = dp[i];
			max_idx = i;
		}
		i++;
	}
	return (max_idx);
}

void	compute_dp_table(int *arr, int *dp, int *prev, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		dp[i] = 1;
		prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (arr[j] < arr[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
}

int	*build_lis_array(int *arr, int *prev, int max_idx, int lis_size)
{
	int	*lis_arr;
	int	i;

	lis_arr = malloc(sizeof(int) * lis_size);
	if (!lis_arr)
		return (NULL);
	i = lis_size - 1;
	while (max_idx >= 0 && i >= 0)
	{
		lis_arr[i] = arr[max_idx];
		if (prev[max_idx] == -1)
			break ;
		max_idx = prev[max_idx];
		i--;
	}
	return (lis_arr);
}
