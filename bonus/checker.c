/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:27:42 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 16:06:38 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void		init_checker_data(t_data *data, int argc, char **argv);
int			read_line(char **line);
void		execute_instruction(t_data *data, char *instruction);

static void	process_instructions(t_data *data)
{
	char	*line;

	while (read_line(&line))
	{
		if (!line)
			break ;
		execute_instruction(data, line);
		free(line);
	}
}

static int	validate_args_input(int argc, char **argv)
{
	if (!validate_args(argc, argv))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	return (1);
}

static void	validate_duplicates(t_data *data)
{
	if (has_duplicates(data->arr, data->size))
	{
		write(2, "Error\n", 6);
		free_data(data);
		exit(1);
	}
}

static void	print_result(t_data *data)
{
	if (check_stack_is_sorted(data->a) && data->b->size == 0)
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!validate_args_input(argc, argv))
		return (1);
	init_checker_data(&data, argc, argv);
	validate_duplicates(&data);
	process_instructions(&data);
	print_result(&data);
	free_data(&data);
	return (0);
}
