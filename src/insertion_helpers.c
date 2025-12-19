/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:40 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:54:41 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

static void	calculate_positions(t_data *data, t_stack_node *cheapest,
		int *pos_a, int *pos_b)
{
	int	target_value;

	target_value = find_target_position(data->a, cheapest->value);
	*pos_a = find_position_of_value(data->a, target_value);
	*pos_b = find_position_of_value(data->b, cheapest->value);
}

void	prepare_and_insert_element(t_data *data, t_stack_node *cheapest)
{
	int	pos_a;
	int	pos_b;
	int	rot_a;
	int	rot_b;

	calculate_positions(data, cheapest, &pos_a, &pos_b);
	rot_a = calculate_rotation_count(pos_a, data->a->size);
	rot_b = calculate_rotation_count(pos_b, data->b->size);
	execute_rotation_operations(data, rot_a, rot_b);
	pa(data->a, data->b);
}
