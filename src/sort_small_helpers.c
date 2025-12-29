/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_smallest_two(t_stack *stack, int *smallest, int *second_smallest)
{
	t_stack_node	*current;
	int				min1;
	int				min2;

	min1 = INT_MAX;
	min2 = INT_MAX;
	current = stack->top;
	while (current)
	{
		if (current->value < min1)
		{
			min2 = min1;
			min1 = current->value;
		}
		else if (current->value < min2)
			min2 = current->value;
		current = current->next;
	}
	*smallest = min1;
	*second_smallest = min2;
	return (0);
}

static void	perform_rotations(t_data *data, int rotations)
{
	while (rotations > 0)
	{
		ra(data->a);
		rotations--;
	}
	while (rotations < 0)
	{
		rra(data->a);
		rotations++;
	}
}

static int	calculate_rotations_needed(t_data *data, int target_value)
{
	int	pos;
	int	rotations;

	pos = find_position_of_value(data->a, target_value);
	rotations = pos;
	if (pos > data->a->size / 2)
		rotations = pos - data->a->size;
	return (rotations);
}

void	insert_from_b_optimally(t_data *data)
{
	int	target_value;
	int	rotations;

	while (data->b->size > 0)
	{
		target_value = find_target_position(data->a, data->b->top->value);
		rotations = calculate_rotations_needed(data, target_value);
		perform_rotations(data, rotations);
		pa(data->a, data->b);
	}
}

void	push_two_smallest_to_b(t_data *data);

void	rotate_to_minimum(t_data *data)
{
	int	min;
	int	rotations;

	min = get_min_value_in_stack(data->a);
	rotations = calculate_rotations_needed(data, min);
	perform_rotations(data, rotations);
}
