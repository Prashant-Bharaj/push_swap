/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:15:00 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:06:35 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	is_valid_zero(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '0' && str[i + 1] == '\0')
		return (1);
	return (0);
}

static void	validate_value(int value, const char *str, t_data *data)
{
	if (value == 0 && !is_valid_zero(str))
	{
		free_data(data);
		write(2, "Error\n", 6);
		exit(1);
	}
}

static void	init_stacks(t_data *data)
{
	data->a = malloc(sizeof(t_stack));
	data->b = malloc(sizeof(t_stack));
	if (!data->a || !data->b)
		error_exit(data, "Error\n");
	init_stack(data->a);
	init_stack(data->b);
}

static void	fill_stack(t_data *data, char **argv)
{
	int	i;
	int	value;

	i = data->size - 1;
	while (i >= 0)
	{
		t_stack_node	*node;

		value = ft_atoi(argv[i + 1]);
		validate_value(value, argv[i + 1], data);
		data->arr[i] = value;
		node = create_node(data->arr[i]);
		if (!node)
		{
			free_data(data);
			write(2, "Error\n", 6);
			exit(1);
		}
		push_node(data->a, node);
		i--;
	}
}

void	init_checker_data(t_data *data, int argc, char **argv)
{
	init_stacks(data);
	data->size = argc - 1;
	data->arr = malloc(sizeof(int) * data->size);
	if (!data->arr)
		error_exit(data, "Error\n");
	fill_stack(data, argv);
}
