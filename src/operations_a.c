/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:59 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:00 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *a)
{
	swap_top_two_nodes(a);
	ft_putstr("sa\n");
}

void	ra(t_stack *a)
{
	rotate_stack_forward(a);
	ft_putstr("ra\n");
}

void	rra(t_stack *a)
{
	rotate_stack_backward(a);
	ft_putstr("rra\n");
}

void	pa(t_stack *a, t_stack *b)
{
	t_stack_node	*node;

	if (!a || !b || !b->top)
		return ;
	node = pop_node(b);
	push_node(a, node);
	ft_putstr("pa\n");
}
