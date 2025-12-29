/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_push_operation(t_data *data)
{
	pb(data->a, data->b);
	if (data->b->size == 2
		&& data->b->top->value < data->b->top->next->value)
		sb(data->b);
}

static void	choose_rotation_direction(t_data *data, int pos1, int pos2)
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

void	push_two_smallest_to_b(t_data *data)
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
			handle_push_operation(data);
		else
			choose_rotation_direction(data, pos1, pos2);
	}
}
