/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:16 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/29 19:21:33 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int					count_numbers(int argc, char **argv);

void				parse_and_add_numbers(t_data *data, int argc, char **argv);

void				build_stack(t_data *data);

void				init_data(t_data *data, int argc, char **argv);

static void	process_input(t_data *data)
{
	if (has_duplicates(data->arr, data->size))
		error_exit(data, "Error\n");
	index_stack(data->a);
	if (check_stack_is_sorted(data->a))
	{
		free_data(data);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!validate_args(argc, argv))
		error_exit(NULL, "Error\n");
	init_data(&data, argc, argv);
	process_input(&data);
	if (data.size <= 5)
		sort_small_stack(&data);
	else
		sort_large_stack(&data);
	free_data(&data);
	return (0);
}
