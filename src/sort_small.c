/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:53:31 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/29 19:21:34 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_elements(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

void					push_two_smallest_to_b(t_data *data);

void					insert_from_b_optimally(t_data *data);

void					rotate_to_minimum(t_data *data);

void	sort_five_elements(t_data *data)
{
	push_two_smallest_to_b(data);
	sort_three_elements(data->a);
	insert_from_b_optimally(data);
	rotate_to_minimum(data);
}

void	sort_small_stack(t_data *data)
{
	if (data->size == 2)
	{
		if (data->a->top->value > data->a->top->next->value)
			sa(data->a);
	}
	else if (data->size == 3)
		sort_three_elements(data->a);
	else if (data->size == 5)
		sort_five_elements(data);
}
