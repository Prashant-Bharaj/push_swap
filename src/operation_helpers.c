/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:05 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:06 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_node	*get_last_node(t_stack *stack)
{
	t_stack_node	*last;

	if (!stack || !stack->top)
		return (NULL);
	last = stack->top;
	while (last->next)
		last = last->next;
	return (last);
}

void	swap_top_two_nodes(t_stack *stack)
{
	t_stack_node	*first;
	t_stack_node	*second;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	stack->top = second;
}

void	rotate_stack_forward(t_stack *stack)
{
	t_stack_node	*first;
	t_stack_node	*last;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	first = stack->top;
	last = get_last_node(stack);
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
}

void	rotate_stack_backward(t_stack *stack)
{
	t_stack_node	*last;
	t_stack_node	*prev;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	last = get_last_node(stack);
	prev = last->prev;
	prev->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}
