/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:50 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:51 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int	find_target_position(t_stack *a, int value)
{
	int	target;
	int	max;
	int	min;

	if (!a || !a->top)
		return (0);
	target = find_smallest_greater_value(a, value);
	if (target == INT_MAX)
	{
		max = get_max_value_in_stack(a);
		min = get_min_value_in_stack(a);
		if (value > max)
			return (min);
		return (max);
	}
	return (target);
}

int	calculate_cost(t_stack_node *node_b, t_stack *a, t_stack *b)
{
	int				cost_a;
	int				cost_b;
	t_stack_node	*target_node;
	int				target_value;

	target_value = find_target_position(a, node_b->value);
	target_node = a->top;
	while (target_node && target_node->value != target_value)
		target_node = target_node->next;
	if (!target_node)
		return (INT_MAX);
	cost_a = get_rotation_cost(a, target_node);
	cost_b = get_rotation_cost(b, node_b);
	if ((cost_a > 0 && cost_b > 0) || (cost_a < 0 && cost_b < 0))
	{
		if (ft_abs(cost_a) > ft_abs(cost_b))
			return (ft_abs(cost_a));
		return (ft_abs(cost_b));
	}
	return (ft_abs(cost_a) + ft_abs(cost_b));
}

void	calculate_costs(t_stack *a, t_stack *b)
{
	t_stack_node	*current;

	current = b->top;
	while (current)
	{
		current->cost = calculate_cost(current, a, b);
		current = current->next;
	}
}

t_stack_node	*find_cheapest_node(t_stack *b)
{
	t_stack_node	*cheapest;
	t_stack_node	*current;

	if (!b || !b->top)
		return (NULL);
	cheapest = b->top;
	current = b->top->next;
	while (current)
	{
		if (current->cost < cheapest->cost)
			cheapest = current;
		current = current->next;
	}
	return (cheapest);
}
