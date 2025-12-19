/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:42 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/19 22:53:43 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int	calculate_rotation_count(int pos, int size)
{
	if (pos > size / 2)
		return (size - pos);
	return (-pos);
}

static void	execute_combined_rotations(t_data *data, int *rot_a, int *rot_b)
{
	while (*rot_a < 0 && *rot_b < 0)
	{
		rr(data->a, data->b);
		(*rot_a)++;
		(*rot_b)++;
	}
	while (*rot_a > 0 && *rot_b > 0)
	{
		rrr(data->a, data->b);
		(*rot_a)--;
		(*rot_b)--;
	}
}

static void	rotate_stack_a(t_data *data, int rot_a)
{
	while (rot_a < 0)
	{
		ra(data->a);
		rot_a++;
	}
	while (rot_a > 0)
	{
		rra(data->a);
		rot_a--;
	}
}

static void	rotate_stack_b(t_data *data, int rot_b)
{
	while (rot_b < 0)
	{
		rb(data->b);
		rot_b++;
	}
	while (rot_b > 0)
	{
		rrb(data->b);
		rot_b--;
	}
}

static void	execute_single_rotations(t_data *data, int rot_a, int rot_b)
{
	rotate_stack_a(data, rot_a);
	rotate_stack_b(data, rot_b);
}

void	execute_rotation_operations(t_data *data, int rot_a, int rot_b)
{
	execute_combined_rotations(data, &rot_a, &rot_b);
	execute_single_rotations(data, rot_a, rot_b);
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
