/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:52:54 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:07:14 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_node	*create_node(int value)
{
	t_stack_node	*node;

	node = malloc(sizeof(t_stack_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->cost = 0;
	node->lis = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	push_node(t_stack *stack, t_stack_node *node)
{
	if (!stack || !node)
		return ;
	if (stack->top)
	{
		node->next = stack->top;
		stack->top->prev = node;
	}
	stack->top = node;
	stack->size++;
}

t_stack_node	*pop_node(t_stack *stack)
{
	t_stack_node	*node;

	if (!stack || !stack->top)
		return (NULL);
	node = stack->top;
	stack->top = node->next;
	if (stack->top)
		stack->top->prev = NULL;
	node->next = NULL;
	stack->size--;
	return (node);
}

void	init_stack(t_stack *stack)
{
	if (!stack)
		return ;
	stack->top = NULL;
	stack->size = 0;
}

void	free_stack(t_stack *stack)
{
	t_stack_node	*current;
	t_stack_node	*next;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->top = NULL;
	stack->size = 0;
}
