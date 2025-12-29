/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:37 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:53:38 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_non_lis_elements_to_b(t_data *data, int *lis_arr, int lis_size)
{
	int				original_size;
	int				i;
	int				rotated_count;
	t_stack_node	*current;

	original_size = data->a->size;
	i = 0;
	while (i < original_size && data->a->size > lis_size)
	{
		current = data->a->top;
		if (!is_in_lis(current, lis_arr, lis_size))
			pb(data->a, data->b);
		else
			ra(data->a);
		i++;
	}
	rotated_count = 0;
	while (data->a->top && is_in_lis(data->a->top, lis_arr, lis_size)
		&& rotated_count < data->a->size)
	{
		ra(data->a);
		rotated_count++;
	}
}

void	insert_elements_optimally(t_data *data)
{
	t_stack_node	*cheapest;

	while (data->b->size > 0)
	{
		calculate_costs(data->a, data->b);
		cheapest = find_cheapest_node(data->b);
		if (!cheapest)
			break ;
		prepare_and_insert_element(data, cheapest);
	}
	rotate_to_minimum_value(data->a);
}

void	sort_large_stack(t_data *data)
{
	int	*lis_arr;
	int	lis_size;

	calculate_lis(data->a);
	lis_arr = find_lis_sequence(data->a, &lis_size);
	if (!lis_arr)
		error_exit(data, "Error\n");
	push_non_lis_elements_to_b(data, lis_arr, lis_size);
	insert_elements_optimally(data);
	free(lis_arr);
}
