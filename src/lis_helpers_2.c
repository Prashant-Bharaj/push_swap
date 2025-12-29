/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_helpers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:48:23 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 17:52:24 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	get_lis_size_from_dp(int *dp, int size)
{
	int	max_idx;

	max_idx = find_max_index(dp, size);
	return (dp[max_idx]);
}

void	free_lis_resources(int *arr, int *dp, int *prev)
{
	free(arr);
	free(dp);
	free(prev);
}
