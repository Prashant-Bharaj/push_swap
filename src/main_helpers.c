/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:00:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 18:00:00 by prasingh          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_numbers(int argc, char **argv)
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
				while (argv[i][j] && argv[i][j] != ' ' && (argv[i][j] < 9
						|| argv[i][j] > 13))
					j++;
			}
		}
		i++;
	}
	return (count);
}

void	parse_and_add_numbers(t_data *data, int argc, char **argv)
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
				while (argv[i][j] && argv[i][j] != ' ' && (argv[i][j] < 9
						|| argv[i][j] > 13))
					j++;
			}
		}
		i++;
	}
}

void	build_stack(t_data *data)
{
	int				i;
	t_stack_node	*node;

	i = data->size - 1;
	while (i >= 0)
	{
		node = create_node(data->arr[i]);
		if (!node)
			error_exit(data, "Error\n");
		push_node(data->a, node);
		i--;
	}
}

void	init_data(t_data *data, int argc, char **argv)
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
