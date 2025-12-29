/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:31 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:53:32 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_elements(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

static int	find_smallest_two(t_stack *stack, int *smallest, int *second_smallest)
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

static void	push_two_smallest_to_b(t_data *data)
{
	int	min1;
	int	min2;
	int	pos1;
	int	pos2;

	find_smallest_two(data->a, &min1, &min2);
	while (data->a->size > 3)
	{
		pos1 = find_position_of_value(data->a, min1);
		pos2 = find_position_of_value(data->a, min2);
		if (pos1 == 0 || pos2 == 0)
		{
			pb(data->a, data->b);
			if (data->b->size == 2 && data->b->top->value < data->b->top->next->value)
				sb(data->b);
		}
		else
		{
			if (pos1 <= 2 && pos2 <= 2)
				ra(data->a);
			else if (pos1 > 2 && pos2 > 2)
				rra(data->a);
			else if (pos1 <= pos2)
				ra(data->a);
			else
				rra(data->a);
		}
	}
}

static void	insert_from_b_optimally(t_data *data)
{
	int	target_value;
	int	pos;
	int	rotations;

	while (data->b->size > 0)
	{
		target_value = find_target_position(data->a, data->b->top->value);
		pos = find_position_of_value(data->a, target_value);
		rotations = pos;
		if (pos > data->a->size / 2)
			rotations = pos - data->a->size;
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
		pa(data->a, data->b);
	}
}

static void	rotate_to_minimum(t_data *data)
{
	int	min;
	int	pos;
	int	rotations;

	min = get_min_value_in_stack(data->a);
	pos = find_position_of_value(data->a, min);
	rotations = pos;
	if (pos > data->a->size / 2)
		rotations = pos - data->a->size;
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

void	sort_five_elements(t_data *data)
{
	push_two_smallest_to_b(data);
	sort_three_elements(data->a);
	insert_from_b_optimally(data);
	rotate_to_minimum(data);
}

void	sort_small_stack(t_data *data)
{
	if (data->size == 2)
	{
		if (data->a->top->value > data->a->top->next->value)
			sa(data->a);
	}
	else if (data->size == 3)
		sort_three_elements(data->a);
	else if (data->size == 5)
		sort_five_elements(data);
}
