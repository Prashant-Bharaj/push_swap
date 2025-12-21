/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:17 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:07:20 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_stack_is_sorted(t_stack *stack)
{
	t_stack_node	*current;

	if (!stack || !stack->top)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int	get_min_value_in_stack(t_stack *stack)
{
	int				min;
	t_stack_node	*current;

	min = INT_MAX;
	current = stack->top;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	get_max_value_in_stack(t_stack *stack)
{
	int				max;
	t_stack_node	*current;

	max = INT_MIN;
	current = stack->top;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}

int	find_position_of_value(t_stack *stack, int value)
{
	int				pos;
	t_stack_node	*current;

	pos = 0;
	current = stack->top;
	while (current && current->value != value)
	{
		pos++;
		current = current->next;
	}
	return (pos);
}
