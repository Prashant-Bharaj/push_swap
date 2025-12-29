/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:15:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:06:32 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	exec_swap(t_data *data, char op)
{
	if (op == 'a')
		swap_top_two_nodes(data->a);
	else if (op == 'b')
		swap_top_two_nodes(data->b);
	else
	{
		swap_top_two_nodes(data->a);
		swap_top_two_nodes(data->b);
	}
}

static void	exec_push(t_data *data, char op)
{
	t_stack_node	*node;

	if (op == 'a' && data->b->top)
	{
		node = pop_node(data->b);
		push_node(data->a, node);
	}
	else if (op == 'b' && data->a->top)
	{
		node = pop_node(data->a);
		push_node(data->b, node);
	}
}

static void	exec_rotate(t_data *data, char op)
{
	if (op == 'a')
		rotate_stack_forward(data->a);
	else if (op == 'b')
		rotate_stack_forward(data->b);
	else
	{
		rotate_stack_forward(data->a);
		rotate_stack_forward(data->b);
	}
}

static void	exec_reverse_rotate(t_data *data, char op)
{
	if (op == 'a')
		rotate_stack_backward(data->a);
	else if (op == 'b')
		rotate_stack_backward(data->b);
	else
	{
		rotate_stack_backward(data->a);
		rotate_stack_backward(data->b);
	}
}

void	execute_instruction(t_data *data, char *inst)
{
	if (!inst || !inst[0])
		return ;
	if (inst[0] == 's' && inst[1] && inst[2] == '\0')
		exec_swap(data, inst[1]);
	else if (inst[0] == 'p' && inst[1] && inst[2] == '\0')
		exec_push(data, inst[1]);
	else if (inst[0] == 'r' && inst[1] == 'r' && inst[2] && inst[3] == '\0')
		exec_reverse_rotate(data, inst[2]);
	else if (inst[0] == 'r' && inst[1] && inst[2] == '\0')
		exec_rotate(data, inst[1]);
	else
	{
		write(2, "Error\n", 6);
		free_data(data);
		exit(1);
	}
}
