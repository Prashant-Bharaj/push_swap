/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:53 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:53:54 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_stack *b)
{
	swap_top_two_nodes(b);
	ft_putstr("sb\n");
}

void	rb(t_stack *b)
{
	rotate_stack_forward(b);
	ft_putstr("rb\n");
}

void	rrb(t_stack *b)
{
	rotate_stack_backward(b);
	ft_putstr("rrb\n");
}

void	pb(t_stack *a, t_stack *b)
{
	t_stack_node	*node;

	if (!a || !b || !a->top)
		return ;
	node = pop_node(a);
	push_node(b, node);
	ft_putstr("pb\n");
}
