/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_both.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:47 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:53:48 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_stack *a, t_stack *b)
{
	swap_top_two_nodes(a);
	swap_top_two_nodes(b);
	ft_putstr("ss\n");
}

void	rr(t_stack *a, t_stack *b)
{
	rotate_stack_forward(a);
	rotate_stack_forward(b);
	ft_putstr("rr\n");
}

void	rrr(t_stack *a, t_stack *b)
{
	rotate_stack_backward(a);
	rotate_stack_backward(b);
	ft_putstr("rrr\n");
}
