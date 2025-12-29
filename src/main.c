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

static int	count_numbers(int argc, char **argv)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] <= 13))
				j++;
			if (argv[i][j])
			{
				count++;
				while (argv[i][j] && argv[i][j] != ' '
					&& (argv[i][j] < 9 || argv[i][j] > 13))
					j++;
			}
		}
		i++;
	}
	return (count);
}

static void	parse_and_add_numbers(t_data *data, int argc, char **argv)
{
	int	i;
	int	j;
	int	idx;

	idx = 0;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] <= 13))
				j++;
			if (argv[i][j])
			{
				data->arr[idx] = ft_atoi(argv[i] + j);
				idx++;
				while (argv[i][j] && argv[i][j] != ' '
					&& (argv[i][j] < 9 || argv[i][j] > 13))
					j++;
			}
		}
		i++;
	}
}

static void	build_stack(t_data *data)
{
	int	i;

	i = data->size - 1;
	while (i >= 0)
	{
		t_stack_node	*node;

		node = create_node(data->arr[i]);
		if (!node)
			error_exit(data, "Error\n");
		push_node(data->a, node);
		i--;
	}
}

static void	init_data(t_data *data, int argc, char **argv)
{
	data->a = malloc(sizeof(t_stack));
	data->b = malloc(sizeof(t_stack));
	if (!data->a || !data->b)
		error_exit(data, "Error\n");
	init_stack(data->a);
	init_stack(data->b);
	data->size = count_numbers(argc, argv);
	if (data->size == 0)
		error_exit(data, "Error\n");
	data->arr = malloc(sizeof(int) * data->size);
	if (!data->arr)
		error_exit(data, "Error\n");
	parse_and_add_numbers(data, argc, argv);
	build_stack(data);
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
	if (data.size <= 5)
		sort_small_stack(&data);
	else
		sort_large_stack(&data);
	free_data(&data);
	return (0);
}
