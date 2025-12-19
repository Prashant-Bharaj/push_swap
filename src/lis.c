/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:21 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:22 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

static int	*allocate_dp_arrays(int size, int **dp, int **prev)
{
	*dp = malloc(sizeof(int) * size);
	*prev = malloc(sizeof(int) * size);
	if (!*dp || !*prev)
		return (NULL);
	return (*dp);
}

static int	*compute_and_build_lis(int *arr, int *dp, int *prev, int size)
{
	int	max_idx;
	int	lis_size;
	int	*lis_arr;

	max_idx = find_max_index(dp, size);
	lis_size = dp[max_idx];
	if (lis_size <= 0)
		return (NULL);
	lis_arr = build_lis_array(arr, prev, max_idx, lis_size);
	return (lis_arr);
}

static int	get_lis_size_from_dp(int *dp, int size)
{
	int	max_idx;

	max_idx = find_max_index(dp, size);
	return (dp[max_idx]);
}

static void	free_lis_resources(int *arr, int *dp, int *prev)
{
	free(arr);
	free(dp);
	free(prev);
}

int	*find_lis_sequence(t_stack *stack, int *lis_size)
{
	int	*arr;
	int	size;
	int	*dp;
	int	*prev;
	int	*lis_arr;

	arr = get_index_array(stack, &size);
	if (!arr || size == 0)
		return (NULL);
	if (!allocate_dp_arrays(size, &dp, &prev))
	{
		free(arr);
		return (NULL);
	}
	compute_dp_table(arr, dp, prev, size);
	*lis_size = get_lis_size_from_dp(dp, size);
	lis_arr = compute_and_build_lis(arr, dp, prev, size);
	if (!lis_arr)
	{
		free_lis_resources(arr, dp, prev);
		return (NULL);
	}
	free_lis_resources(arr, dp, prev);
	return (lis_arr);
}

int	is_in_lis(t_stack_node *node, int *lis_arr, int lis_size)
{
	int	i;

	i = 0;
	while (i < lis_size)
	{
		if (node->index == lis_arr[i])
			return (1);
		i++;
	}
	return (0);
}

void	calculate_lis(t_stack *stack)
{
	int				*lis_arr;
	int				lis_size;
	t_stack_node	*current;

	lis_arr = find_lis_sequence(stack, &lis_size);
	if (!lis_arr)
		return ;
	current = stack->top;
	while (current)
	{
		if (is_in_lis(current, lis_arr, lis_size))
			current->lis = 1;
		else
			current->lis = 0;
		current = current->next;
	}
	free(lis_arr);
}
