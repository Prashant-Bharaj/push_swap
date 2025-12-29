/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:44:27 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 17:47:00 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calculate_rotation_count(int pos, int size)
{
	if (pos > size / 2)
		return (size - pos);
	return (-pos);
}

void	rotate_to_minimum_value(t_stack *a)
{
	int	min;
	int	pos;
	int	size;
	int	rotated;

	min = get_min_value_in_stack(a);
	pos = find_position_of_value(a, min);
	size = a->size;
	rotated = 0;
	if (pos > size / 2)
	{
		while (a->top->value != min && rotated < size)
		{
			rra(a);
			rotated++;
		}
	}
	else
	{
		while (a->top->value != min && rotated < size)
		{
			ra(a);
			rotated++;
		}
	}
}
