/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:54:16 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:07:07 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->a = malloc(sizeof(t_stack));
	data->b = malloc(sizeof(t_stack));
	if (!data->a || !data->b)
		error_exit(data, "Error\n");
	init_stack(data->a);
	init_stack(data->b);
	data->size = argc - 1;
	data->arr = malloc(sizeof(int) * data->size);
	if (!data->arr)
		error_exit(data, "Error\n");
	i = data->size - 1;
	while (i >= 0)
	{
		data->arr[i] = ft_atoi(argv[i + 1]);
		push_node(data->a, create_node(data->arr[i]));
		i--;
	}
}

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
	if (data.size <= 3)
		sort_small_stack(&data);
	else
		sort_large_stack(&data);
	free_data(&data);
	return (0);
}
