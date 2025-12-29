/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:54 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:06:49 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_rotation_cost(t_stack *stack, t_stack_node *node)
{
	int				cost;
	t_stack_node	*current;

	cost = 0;
	current = stack->top;
	while (current != node)
	{
		cost++;
		current = current->next;
	}
	if (cost > stack->size / 2)
		cost = cost - stack->size;
	return (cost);
}

int	find_smallest_greater_value(t_stack *a, int value)
{
	t_stack_node	*current;
	int				target;

	target = INT_MAX;
	current = a->top;
	while (current)
	{
		if (current->value > value && current->value < target)
			target = current->value;
		current = current->next;
	}
	return (target);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
